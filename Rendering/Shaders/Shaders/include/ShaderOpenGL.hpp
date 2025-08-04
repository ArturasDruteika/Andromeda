#ifndef RENDERER__SHADER_OPENGL__HPP
#define RENDERER__SHADER_OPENGL__HPP


#include "ShaderProgramOpenGL.hpp"
#include "UniformSetterOpenGL.hpp"
#include "ShaderSourceManagerOpenGL.hpp"
#include "../../Interfaces/include/IShader.hpp"

namespace Andromeda::Rendering
{
	class ShaderOpenGL
		: public ShaderProgramOpenGL
		, public ShaderSourceManagerOpenGL
		, public IShader
	{
	public:
		ShaderOpenGL(const std::filesystem::path& vertexCodeFilePath, const std::filesystem::path& fragmentCodeFilePath);
		~ShaderOpenGL() = default;

		void Bind() const override;
		void UnBind() const override;

		// Setters for Uniforms
		template<typename T>
		void SetUniform(const std::string& name, const T& value) const;

	private:
		UniformSetterOpenGL m_uniformSetter;
	};
}

#endif // RENDERER__SHADER_OPENGL__HPP
