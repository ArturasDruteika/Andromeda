#ifndef RENDERER__SHADER_SOURCE_MANAGER_OPENGL__HPP
#define RENDERER__SHADER_SOURCE_MANAGER_OPENGL__HPP


#include "pch.hpp"
#include "../../Support/include/ShaderTypes.hpp"


namespace Andromeda::Rendering
{
	class ShaderSourceManagerOpenGL
	{
	public:
		ShaderSourceManagerOpenGL(
			const std::filesystem::path& vertexShaderFilepath,
			const std::filesystem::path& fragmentShaderFilepath,
			const std::filesystem::path& geometryShaderFilepath = {},
			bool load = true
		);
		~ShaderSourceManagerOpenGL();

		// Getters
		const std::filesystem::path& GetVertexShaderPath() const;
		const std::filesystem::path& GetFragmentShaderPath() const;
		const std::filesystem::path& GetGeometryShaderPath() const;
		const std::string& GetVertexCode() const;
		const std::string& GetFragmentCode() const;
		const std::string& GetGeometryCode() const;

		void LoadShaderFromFile(const ShaderType& shaderType, const std::filesystem::path& filepath);

	protected:
		std::filesystem::path m_vertexShaderPath;
		std::filesystem::path m_fragmentShaderPath;
		std::filesystem::path m_geometryShaderPath;
		std::string m_vertexCode;
		std::string m_fragmentCode;
		std::string m_geometryCode;
	};
}


#endif // RENDERER__SHADER_SOURCE_MANAGER_OPENGL__HPP