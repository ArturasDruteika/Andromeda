#ifndef RENDERER__SHADER_MANAGER__HPP
#define RENDERER__SHADER_MANAGER__HPP


#include "pch.hpp"
#include "../../Support/include/ShaderOpenGLTypes.hpp"
#include "ShaderOpenGL.hpp"


namespace Andromeda::Rendering
{
	class ShaderManager
	{
	public:
		ShaderManager(bool initShaders);
		~ShaderManager();

		// Getters
		bool IsInitialized() const;
		ShaderOpenGL* GetShader(const ShaderOpenGLTypes& shaderType) const;
		const std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*>& GetShadersMap() const;

		bool InitShaders();
		bool LoadShader(const ShaderOpenGLTypes& shaderType, const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);

	private:
		bool CreateShader(const ShaderOpenGLTypes& shaderType, const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);
		bool ValidateShaderPaths(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
		bool CheckShaderPath(const std::filesystem::path& path, const std::string& type);

	private:
		bool m_isInitialized;
		std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*> m_shadersMap;
	};
}


#endif // RENDERER__SHADER_MANAGER__HPP