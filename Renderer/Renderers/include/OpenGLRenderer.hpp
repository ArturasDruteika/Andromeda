#ifndef RENDERER__OPENGL_RENDERER__HPP
#define RENDERER__OPENGL_RENDERER__HPP


#include <glad/gl.h> // Include OpenGL functions
#include "../../Shaders/include/OpenGLShader.hpp"


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
			unsigned int CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

			bool m_isInitialized;
			// VBO - vertex buffer obj
			// VAO - vertex array obj
			unsigned int m_VBO, m_VAO;
			OpenGLShader* m_shader;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER__HPP