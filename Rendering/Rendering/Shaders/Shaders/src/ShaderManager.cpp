#include "../include/ShaderManager.hpp"
#include "Utils/FileOperations/include/FileOperations.hpp"
#include "spdlog/spdlog.h"


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
                "shader_program_sources/vertex.glsl",
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
            },
            {
                ShaderOpenGLTypes::PointShadowCubeMap,
                "shader_program_sources/vertex_point_shadow.glsl",
                "shader_program_sources/fragment_point_shadow.glsl",
                "shader_program_sources/geometry_point_shadow.glsl"
            }
        };

        for (const auto& shader : shaders)
        {
            if (!CreateShader(shader.type, shader.vertexPath, shader.fragmentPath, shader.geometryPath))
            {
                // If any shader fails to load/compile, return false immediately
                return false;
            }
        }

        m_isInitialized = true;
        return true;
    }

    bool ShaderManager::LoadShader(
        const ShaderOpenGLTypes& shaderType,
        const std::filesystem::path& vertexShaderPath,
        const std::filesystem::path& fragmentShaderPath,
        const std::filesystem::path& geometryShaderPath
    )
    {
        if (!ValidateShaderPaths(vertexShaderPath, fragmentShaderPath, geometryShaderPath))
        {
            return false;
        }

        if (m_shadersMap.find(shaderType) != m_shadersMap.end())
        {
            spdlog::warn("Shader of type {} already exists. Overwriting.", static_cast<int>(shaderType));
            delete m_shadersMap[shaderType];
            m_shadersMap.erase(shaderType);
        }

        if (m_shadersMap.find(shaderType) != m_shadersMap.end())
        {
            spdlog::warn("Shader of type {} already exists. Overwriting.", static_cast<int>(shaderType));
            delete m_shadersMap[shaderType];
            m_shadersMap.erase(shaderType);
        }
        return CreateShader(shaderType, vertexShaderPath, fragmentShaderPath, geometryShaderPath);
    }

    bool ShaderManager::CreateShader(
        const ShaderOpenGLTypes& shaderType, 
        const std::filesystem::path& vertexShaderPath, 
        const std::filesystem::path& fragmentShaderPath,
        const std::filesystem::path& geometryShaderPath
    )
    {
        ShaderOpenGL* shader = new ShaderOpenGL(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
        m_shadersMap.insert({ shaderType, shader });

		// TODO: Add error handling for shader creation
        return true;
    }

    bool ShaderManager::ValidateShaderPaths(
        const std::filesystem::path& vertexPath, 
        const std::filesystem::path& fragmentPath,
        const std::filesystem::path& geometryPath
        )
    {
        bool status = true;
        if (!vertexPath.empty())
            status = CheckShaderPath(vertexPath, "Vertex");
        else
            status = false;
        if (!fragmentPath.empty())
            status = CheckShaderPath(fragmentPath, "Fragment");
        else
            status = false;
        if (!geometryPath.empty())
            status = CheckShaderPath(geometryPath, "Geometry");
        return status;
    }

    bool ShaderManager::CheckShaderPath(const std::filesystem::path& path, const std::string& type)
    {
        if (!std::filesystem::exists(path))
        {
            spdlog::error("{} shader file does not exist: {}", type, path.string());
            return false;
        }

        if (path.extension() != ".glsl")
        {
            spdlog::error("{} shader file must have .glsl extension: {}", type, path.string());
            return false;
        }

        return true;
    }
}
