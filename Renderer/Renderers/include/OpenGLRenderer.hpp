#ifndef RENDERER__OPENGL_RENDERER__HPP
#define RENDERER__OPENGL_RENDERER__HPP


#include "../../Shaders/include/OpenGLShader.hpp"
#include "OpenGLScene.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLRenderer
		{
		public:
			OpenGLRenderer();
			~OpenGLRenderer();

			OpenGLRenderer(const OpenGLRenderer& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderer& operator=(const OpenGLRenderer& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderer(OpenGLRenderer&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderer& operator=(OpenGLRenderer&& other) noexcept = delete;	// Prevent Move Assignment

			void Init(int width, int height);
			void DeInit();
			void RenderFrame(const Environment::OpenGLScene& scene, int width, int height);

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


#endif // RENDERER__OPENGL_RENDERER__HPP