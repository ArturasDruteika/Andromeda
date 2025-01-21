#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../include/OpenGLRenderer.hpp"
#include "../../Shaders/include/OpenGLShader.hpp"
#include <glad/gl.h>



namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLRenderer::OpenGLRendererImpl
		{
		public:
			OpenGLRendererImpl();
			~OpenGLRendererImpl();

			OpenGLRendererImpl(const OpenGLRendererImpl& other) = delete;	// Prevent Copy Constructor
			OpenGLRendererImpl& operator=(const OpenGLRendererImpl& other) = delete;	// Prevent Copy Assignment
			OpenGLRendererImpl(OpenGLRendererImpl&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRendererImpl& operator=(OpenGLRendererImpl&& other) noexcept = delete;	// Prevent Move Assignment

			bool IsInitialized() const;
			void Initialize(const char* name);
			void RenderFrame(const Environment::OpenGLScene& scene);
			void Shutdown();

			unsigned int GetFrameBufferObject();
			unsigned int GetFrameBufferObjectTexture();

		private:
			void InitFrameBuffer();
			void LoadGlad(GLADloadfunc load);
			void CreateShader();
				 
			bool m_isInitialized;
			unsigned int m_FBO, m_FBOTexture;
			OpenGLShader* m_shader;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP