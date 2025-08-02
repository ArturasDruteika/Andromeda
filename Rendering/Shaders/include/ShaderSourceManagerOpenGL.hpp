#ifndef RENDERER__SHADER_SOURCE_MANAGER_OPENGL__HPP
#define RENDERER__SHADER_SOURCE_MANAGER_OPENGL__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
	class ShaderSourceManagerOpenGL
	{
	public:
		ShaderSourceManagerOpenGL(
			const std::string& vertexShaderFilepath,
			const std::string& fragmentShaderFilepath,
			bool load
		);
		~ShaderSourceManagerOpenGL();

		// Getters
		const std::string& GetVertexShaderPath() const;
		const std::string& GetFragmentShaderPath() const;
		const std::string& GetVertexCode() const;
		const std::string& GetFragmentCode() const;

		void LoadVertexShaderFromFile(const std::string& filepath);
		void LoadFragmentShaderFromFile(const std::string& filepath);

	protected:
		std::string m_vertexShaderPath;
		std::string m_fragmentShaderPath;
		std::string m_vertexCode;
		std::string m_fragmentCode;
	};
}


#endif // RENDERER__SHADER_SOURCE_MANAGER_OPENGL__HPP