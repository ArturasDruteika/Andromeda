#ifndef RENDERER__OPENGL_RENDERER__HPP
#define RENDERER__OPENGL_RENDERER__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Interfaces/include/IRendererOpenGL.hpp"
#include "Andromeda/Space/Scene/IScene.hpp"
#include "Andromeda/Space/Camera/ICamera.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API RendererOpenGL
		: public IRendererOpenGL
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();

		RendererOpenGL(const RendererOpenGL& other) = delete;	// Prevent Copy Constructor
		RendererOpenGL& operator=(const RendererOpenGL& other) = delete;	// Prevent Copy Assignment
		RendererOpenGL(RendererOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
		RendererOpenGL& operator=(RendererOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

		// Getters
		bool IsInitialized() const override;
		bool IsGridVisible() const override;
		bool IsIlluminationMode() const override;
		unsigned int GetFrameBufferTexture() const override;
		int GetWidth() const override;
		int GetHeight() const override;
		// Setters
		void SetGridVisible(bool visible) override;
		void SetIlluminationMode(bool mode) override;

		void Init(int width, int height, bool illuminationMode = false) override;
		void DeInit() override;
		void RenderFrame(IScene& scene) override;
		void Resize(int width, int height) override;

	private:
		class RendererOpenGLImpl;
		RendererOpenGLImpl* m_pRendererOpenGLImpl;
	};
}


#endif // RENDERER__OPENGL_RENDERER__HPP