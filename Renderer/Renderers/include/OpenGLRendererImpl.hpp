#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../include/OpenGLRenderer.hpp"
#include "../../Shaders/include/OpenGLShader.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLRenderer::OpenGLRendererImpl
		{
		public:
			OpenGLRendererImpl(OpenGLRenderer& parent);
			~OpenGLRendererImpl();

			bool IsInitialized() const;
			void Initialize(GLADloadfunc load);
			void RenderFrame();
			void Shutdown();

		private:
			void LoadGlad(GLADloadfunc load);
			void SetupTriangle();

			OpenGLRenderer m_parent;
			bool m_isInitialized;
			// VBO - vertex buffer obj
			// VAO - vertex array obj
			unsigned int m_VBO, m_VAO;
			OpenGLShader* m_shader;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP