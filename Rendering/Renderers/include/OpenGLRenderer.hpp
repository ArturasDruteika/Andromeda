#ifndef RENDERER__OPENGL_RENDERER__HPP
#define RENDERER__OPENGL_RENDERER__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "../../Scene/include/OpenGLScene.hpp"
#include "../../Camera/include/Camera.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API OpenGLRenderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		OpenGLRenderer(const OpenGLRenderer& other) = delete;	// Prevent Copy Constructor
		OpenGLRenderer& operator=(const OpenGLRenderer& other) = delete;	// Prevent Copy Assignment
		OpenGLRenderer(OpenGLRenderer&& other) noexcept = delete;	// Prevent Move Constructor
		OpenGLRenderer& operator=(OpenGLRenderer&& other) noexcept = delete;	// Prevent Move Assignment

		// Getters
		bool IsInitialized() const;
		bool IsGridVisible() const;
		bool IsIlluminationMode() const;
		unsigned int GetFrameBufferObject() const;
		unsigned int GetFrameBufferObjectTexture() const;
		unsigned int GetDepthRenderBuffer() const;
		unsigned int GetShadowMap() const;
		int GetWidth() const;
		int GetHeight() const;
		// Setters
		void SetGridVisible(bool visible);
		void SetIlluminationMode(bool mode);
		void SetCamera(Camera* camera);

		void Init(int width, int height, bool illuminationMode = false);
		void DeInit();
		void RenderFrame(OpenGLScene& scene);
		void Resize(int width, int height);

	private:
		class OpenGLRendererImpl;
		OpenGLRendererImpl* m_pOpenGLRendererImpl;
	};
}


#endif // RENDERER__OPENGL_RENDERER__HPP