#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../include/OpenGLRenderer.hpp"
#include "../include/FrameBufferOpenGL.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "../../../Shaders/include/ShaderManager.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
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

		// Getters
		bool IsInitialized() const;
		bool IsGridVisible() const;
		bool IsIlluminationMode() const;
		unsigned int GetFrameBufferObject() const;
		unsigned int GetFrameBufferTexture() const;
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
		void RenderFrame(IScene& scene);
		void Resize(int width, int height);

	private:
		void ShadowMapDepthPass(const IScene& scene, const glm::mat4& lightSpace) const;
		void RenderNonLuminousObjects(const IScene& scene, const glm::mat4& lightSpace) const;
		void RenderLuminousObjects(const IScene& scene) const;
		void RenderObjects(const IScene& scene) const;
		void RenderGrid(const IRenderableObjectOpenGL& object) const;
		void UpdatePerspectiveMatrix(int width, int height);
		void BeginFrame() const;
		void EndFrame() const;
		void LogFPS() const;
		void EnableFaceCulling(unsigned int face, unsigned int winding) const;
		void DisableFaceCulling() const;
		void PrepareFramebufferForNonLuminousPass() const;
		void BindShadowMap(int textureUnit) const;
		void RenderGridIfVisible(const IScene& scene) const;
		void PopulateLightUniforms(OpenGLShader& shader, const IScene& scene) const;
		void RenderEachNonLuminousObject(OpenGLShader& shader, const IScene& scene) const;
		glm::mat4 ComputeLightSpaceMatrix(const IScene& scene) const;

	private:
		bool m_isInitialized;
		bool m_isGridVisible;
		bool m_isIlluminationMode;
		int m_width;
		int m_height;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_lightSpace;
		FrameBufferOpenGL m_mainFBO;
		FrameBufferOpenGL m_shadowFBO;
		Camera* m_pCamera;
		ShaderManager* m_pShaderManager;
		mutable std::chrono::steady_clock::time_point m_lastFrameTime = std::chrono::steady_clock::now();
	};
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP