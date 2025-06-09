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


namespace Andromeda
{
	namespace Rendering
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
			class OpenGLRendererImpl;
			OpenGLRendererImpl* m_pOpenGLRendererImpl;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER__HPP