#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../include/OpenGLRenderer.hpp"
#include "../../Shaders/include/OpenGLShader.hpp"


namespace Andromeda
{
	namespace Rendering
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

			void Init(int width, int height);
			void DeInit();
			void RenderFrame(const Rendering::OpenGLScene& scene, int width, int height);

			bool IsInitialized() const;
			unsigned int GetFrameBufferObject() const;
			unsigned int GetFrameBufferObjectTexture() const;

		private:
			void InitFrameBuffer(int width, int height);
			void CreateShader();

			bool m_isInitialized;
			unsigned int m_FBO, m_FBOTexture;
			OpenGLShader* m_shader;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP