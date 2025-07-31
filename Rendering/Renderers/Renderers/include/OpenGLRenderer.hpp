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


#include "../../Interfaces/include/IRendererOpenGL.hpp"
#include "../../../Scene/Interfaces/include/IScene.hpp"
#include "../../../Camera/include/Camera.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API OpenGLRenderer
		: public IRendererOpenGL
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		OpenGLRenderer(const OpenGLRenderer& other) = delete;	// Prevent Copy Constructor
		OpenGLRenderer& operator=(const OpenGLRenderer& other) = delete;	// Prevent Copy Assignment
		OpenGLRenderer(OpenGLRenderer&& other) noexcept = delete;	// Prevent Move Constructor
		OpenGLRenderer& operator=(OpenGLRenderer&& other) noexcept = delete;	// Prevent Move Assignment

		// Getters
		bool IsInitialized() const override;
		bool IsGridVisible() const override;
		bool IsIlluminationMode() const override;
		unsigned int GetFrameBufferID() const override;
		unsigned int GetFrameBufferTexture() const override;
		int GetWidth() const override;
		int GetHeight() const override;
		// Setters
		void SetGridVisible(bool visible) override;
		void SetIlluminationMode(bool mode) override;
		void SetCamera(ICamera* camera) override;

		void Init(int width, int height, bool illuminationMode = false) override;
		void DeInit() override;
		void RenderFrame(IScene& scene) override;
		void Resize(int width, int height) override;

	private:
		class OpenGLRendererImpl;
		OpenGLRendererImpl* m_pOpenGLRendererImpl;
	};
}


#endif // RENDERER__OPENGL_RENDERER__HPP