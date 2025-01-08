#ifndef RENDERER__SHADER__HPP
#define RENDERER__SHADER__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLShader
		{
		public:
			OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode);
			~OpenGLShader();

		private:
		};
	}
}


#endif // RENDERER__SHADER__HPP