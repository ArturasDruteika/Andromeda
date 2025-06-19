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
			unsigned int GetDepthBuffer() const;
			int GetWidth() const;
			int GetHeight() const;
			float GetAmbientStrength() const;
			float GetSpecularStrength() const;
			float GetShininess() const;
			float GetAttenuationConstant() const;
			float GetAttenuationLinear() const;
			float GetAttenuationQuadratic() const;
			// Setters
			void SetGridVisible(bool visible);
			void SetIlluminationMode(bool mode);
			void SetCamera(Camera* camera);
			void SetAmbientStrength(float ambientStrength);
			void SetSpecularStrength(float specularStrength);
			void SetShininess(float shininess);
			void SetAttenuationConstant(float attenuationConstant);
			void SetAttenuationLinear(float attenuationLinear);
			void SetAttenuationQuadratic(float attenuationQuadratic);

			void Init(int width, int height);
			void DeInit();
			void RenderFrame(const OpenGLScene& scene) const;
			void Resize(int width, int height);

		private:
			void InitFrameBuffer();
			void CreateShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			void GenerateAndBindFrameBuffer();
			void GenerateAndBindFrameBufferTexture();
			void CreateColorTexture();
			void CreateDepthRenderBuffer();
			void SetDrawBuffer();
			void CheckFBOStatus();
			void ConfigureFrameBufferTexture();
			void UnbindFrameBuffer() const;
			void RenderObject(const IRenderableObjectOpenGL& object) const;
			void RenderObjectWithIllumination(
				const IRenderableObjectOpenGL& object,
				const std::unordered_map<int, Math::Vec3>& lightEmittingObjectCoords,
				const std::unordered_map<int, Math::Vec4>& lightEmittingObjectColors,
				const std::unordered_map<int, LuminousBehavior*>& lightEmittingObjectBehaviors
			) const;
			void RenderObjects(const OpenGLScene& scene) const;
			void RenderGrid(const IRenderableObjectOpenGL& object) const;
			void InitShaders();
			void UpdatePerspectiveMatrix(int width, int height);

		private:
			bool m_isInitialized;
			bool m_isGridVisible;
			bool m_isIlluminationMode;
			unsigned int m_FBO;
			unsigned int m_FBOTexture;
			unsigned int m_depthBuffer;
			int m_width;
			int m_height;
			float m_ambientStrength;
			float m_specularStrength;
			float m_shininess;
			float m_attenuationConstant;
			float m_attenuationLinear;
			float m_attenuationQuadratic;
			std::unordered_map<ShaderOpenGLTypes, OpenGLShader*> m_shadersMap;
			glm::mat4 m_projectionMatrix;
			Camera* m_pCamera;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP