#ifndef RENDERER__OPENGL_RENDERER__HPP
#define RENDERER__OPENGL_RENDERER__HPP


#include <glad/gl.h> // Include OpenGL functions


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLRenderer
		{
		public:
			OpenGLRenderer();
			~OpenGLRenderer();

			bool IsInitialized() const;
			void Initialize(GLADloadfunc load);
			void RenderFrame();
			void Shutdown();

		private:
			void LoadGlad(GLADloadfunc load);
			void SetupTriangle();
			GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
			void CheckCompileErrors(GLuint shader, const std::string& type);

			bool m_isInitialized;
			GLuint m_VAO, m_VBO, m_program;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER__HPP