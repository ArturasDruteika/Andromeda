#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "OpenGLRenderer.hpp"
#include <glad/gl.h> // Include OpenGL functions


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLRenderer::OpenGLRendererImpl
		{
		public:
			OpenGLRendererImpl(OpenGLRenderer& parent);
			~OpenGLRendererImpl();

			void Initialize();
			void RenderFrame();
			void Shutdown();

		private:
			void SetupTriangle();
			GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
			void CheckCompileErrors(GLuint shader, const std::string& type);

			OpenGLRenderer& m_parent;
			GLuint m_VAO, m_VBO, m_program;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP