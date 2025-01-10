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
				OpenGLRendererImpl();
				~OpenGLRendererImpl();

				OpenGLRendererImpl(const OpenGLRendererImpl& other);             // Copy Constructor
				OpenGLRendererImpl& operator=(const OpenGLRendererImpl& other);  // Copy Assignment
				OpenGLRendererImpl(OpenGLRendererImpl&& other) noexcept;         // Move Constructor
				OpenGLRendererImpl& operator=(OpenGLRendererImpl&& other) noexcept; // Move Assignment

				bool IsInitialized() const;
				void Initialize(GLADloadfunc load);
				void RenderFrame();
				void Shutdown();

			private:
				void LoadGlad(GLADloadfunc load);
				void SetupTriangle();

				bool m_isInitialized;
				// VBO - vertex buffer obj
				// VAO - vertex array obj
				unsigned int m_VBO, m_VAO;
				OpenGLShader* m_shader;
			};
		}
	}


	#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP