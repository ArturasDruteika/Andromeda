#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../include/OpenGLRenderer.hpp"
#include "../../Shaders/include/OpenGLShader.hpp"
#include "../../Shaders/include/ShaderOpenGLTypes.hpp"
#include "../../RenderableObjects/include/IRenderableObjectOpenGL.hpp"
#include "glm/glm.hpp"


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
			void InitFrameBuffer();
			void InitShadowMap(int width, int height);
			void CreateShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			void GenerateAndBindFrameBuffer();
			void CreateColorTexture();
			void CreateRenderBuffer();
			void SetDrawBuffer();
			void CheckFBOStatus();
			void ConfigureFrameBufferTexture();
			void UnbindFrameBuffer() const;
			void ShadowMapDepthPass(const OpenGLScene& scene, const glm::mat4& lightSpace) const;
			void RenderNonLuminousObjects(const OpenGLScene& scene, const glm::mat4& lightSpace) const;
			void RenderLuminousObjects(const OpenGLScene& scene) const;
			void RenderObjects(const OpenGLScene& scene) const;
			void RenderGrid(const IRenderableObjectOpenGL& object) const;
			void InitShaders();
			void UpdatePerspectiveMatrix(int width, int height);
			void BeginFrame() const;
			void EndFrame() const;
			void LogFPS() const;
			void EnableFaceCulling(unsigned int face, unsigned int winding) const;
			void DisableFaceCulling() const;
			void PrepareFramebufferForNonLuminousPass() const;
			void BindShadowMap(int textureUnit)const;
			void RenderGridIfVisible(const OpenGLScene& scene) const;
			void PopulateLightUniforms(OpenGLShader& shader, const OpenGLScene& scene) const;
			void RenderEachNonLuminousObject(OpenGLShader& shader, const OpenGLScene& scene) const;
			glm::mat4 ComputeLightSpaceMatrix(const OpenGLScene& scene) const;

		private:
			bool m_isInitialized;
			bool m_isGridVisible;
			bool m_isIlluminationMode;
			unsigned int m_FBO;
			unsigned int m_RBO;
			unsigned int m_shadowFBO;
			unsigned int m_FBOTexture;
			unsigned int m_shadowMapTexture;
			int m_width;
			int m_height;
			std::unordered_map<ShaderOpenGLTypes, OpenGLShader*> m_shadersMap;
			glm::mat4 m_projectionMatrix;
			glm::mat4 m_lightSpace;
			Camera* m_pCamera;
			mutable std::chrono::steady_clock::time_point m_lastFrameTime = std::chrono::steady_clock::now();
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP