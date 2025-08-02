#ifndef RENDERER__SHADER_MANAGER__HPP
#define RENDERER__SHADER_MANAGER__HPP


#include "pch.hpp"
#include "ShaderOpenGLTypes.hpp"
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
		bool LoadShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	private:
		bool CreateShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	private:
		bool m_isInitialized;
		std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*> m_shadersMap;
	};
}


#endif // RENDERER__SHADER_MANAGER__HPP