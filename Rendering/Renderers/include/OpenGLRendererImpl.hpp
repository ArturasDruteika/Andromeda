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

			void Init(int width, int height);
			void DeInit();
			void RenderFrame(const OpenGLScene& scene);
			void Resize(int width, int height);

			// Getters
			bool IsInitialized() const;
			unsigned int GetFrameBufferObject() const;
			unsigned int GetFrameBufferObjectTexture() const;
			unsigned int GetDepthBuffer() const;
			int GetWidth() const;
			int GetHeight() const;
			float GetAmbientStrength() const;
			float GetSpecularStrength() const;
			float GetShininess() const;
			// Setters
			void SetCamera(Camera* camera);
			void SetAmbientStrength(float ambientStrength);
			void SetSpecularStrength(float specularStrength);
			void SetShininess(float shininess);

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
			void RenderObject(const IRenderableObjectOpenGL& object);
			void InitShaders();

		private:
			bool m_isInitialized;
			unsigned int m_FBO;
			unsigned int m_FBOTexture;
			unsigned int m_depthBuffer;
			int m_width;
			int m_height;
			float m_ambientStrength;
			float m_specularStrength;
			float m_shininess;
			std::unordered_map<ShaderOpenGLTypes, OpenGLShader*> m_shadersMap;
			glm::mat4 m_projectionMatrix;
			Camera* m_pCamera;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP