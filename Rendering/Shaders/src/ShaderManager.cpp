#include "../include/ShaderManager.hpp"
#include "FileOperations.hpp"


namespace Andromeda::Rendering
{
	ShaderManager::ShaderManager(bool initShaders)
		: m_isInitialized{ false }
	{
        if (initShaders)
        {
            InitShaders();
        }
	}

	ShaderManager::~ShaderManager()
	{
        for (auto& pair : m_shadersMap)
        {
            delete pair.second; // Clean up dynamically allocated ShaderOpenGL objects
        }
        m_shadersMap.clear(); // Clear the map
		spdlog::info("ShaderManager destroyed and all shaders cleaned up.");
	}

    bool ShaderManager::IsInitialized() const
    {
        return m_isInitialized;
	}

    ShaderOpenGL* ShaderManager::GetShader(const ShaderOpenGLTypes& shaderType) const
    {
        auto it = m_shadersMap.find(shaderType);
        if (it == m_shadersMap.end() || it->second == nullptr)
        {
			spdlog::error("Shader of type {} not found in ShaderManager", static_cast<int>(shaderType));
            return nullptr;
        }

        return it->second; // assuming the map stores raw pointers
    }

    const std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*>& ShaderManager::GetShadersMap() const
    {
        return m_shadersMap;
    }

    bool ShaderManager::InitShaders()
    {
        std::vector<ShaderDefinition> shaders = {
            {
                ShaderOpenGLTypes::RenderableObjects,
                "shader_program_sources/vertex.glsl",
                "shader_program_sources/fragment.glsl"
            },
            {
                ShaderOpenGLTypes::Grid,
                "shader_program_sources/vertex_grid.glsl",
                "shader_program_sources/fragment_grid.glsl"
            },
            {
                ShaderOpenGLTypes::RenderableObjectsLuminous,
                "shader_program_sources/vertex_illumination.glsl",
                "shader_program_sources/fragment_luminous_objects.glsl"
            },
            {
                ShaderOpenGLTypes::RenderableObjectsNonLuminous,
                "shader_program_sources/vertex_illumination.glsl",
                "shader_program_sources/fragment_non_luminous_objects.glsl"
            },
            {
                ShaderOpenGLTypes::ShadowMap,
                "shader_program_sources/vertex_depth_only.glsl",
                "shader_program_sources/fragment_depth_only.glsl"
            }
        };

        for (const auto& shader : shaders)
        {
            if (!CreateShader(shader.type, shader.vertexPath, shader.fragmentPath))
            {
                // If any shader fails to load/compile, return false immediately
                return false;
            }
        }

        m_isInitialized = true;
        return true;
    }

    bool ShaderManager::LoadShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        if (m_shadersMap.find(shaderType) != m_shadersMap.end())
        {
            spdlog::warn("Shader of type {} already exists. Overwriting.", static_cast<int>(shaderType));
            delete m_shadersMap[shaderType];
            m_shadersMap.erase(shaderType);
        }
        return CreateShader(shaderType, vertexShaderPath, fragmentShaderPath);
    }

    bool ShaderManager::CreateShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        std::string vertexShaderSource = Utils::FileOperations::LoadFileAsString(vertexShaderPath);
        std::string fragmentShaderSource = Utils::FileOperations::LoadFileAsString(fragmentShaderPath);

        if (vertexShaderSource.empty() || fragmentShaderSource.empty())
        {
            // Failed to load shader files
			spdlog::error("Failed to load shader files for type {}. Check file paths: {}, {}", static_cast<int>(shaderType), vertexShaderPath, fragmentShaderPath);
            return false;
        }

        ShaderOpenGL* shader = new ShaderOpenGL(vertexShaderSource, fragmentShaderSource);
        auto result = m_shadersMap.insert({ shaderType, shader });

        // If insertion fails (shaderType already exists), free memory and return false
        if (!result.second)
        {
			spdlog::error("Failed to create shader of type {}. It may already exist.", static_cast<int>(shaderType));
            delete shader;
            return false;
        }

        return true;
    }
}
