#ifndef ENVIRONMENT__RENDERABLE_OBJECT__HPP
#define ENVIRONMENT__RENDERABLE_OBJECT__HPP


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


#include "pch.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API OpenGLRenderableObject
		{	
		public:
			OpenGLRenderableObject(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
			~OpenGLRenderableObject();

			OpenGLRenderableObject(const OpenGLRenderableObject& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderableObject& operator=(const OpenGLRenderableObject& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderableObject(OpenGLRenderableObject&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderableObject& operator=(OpenGLRenderableObject&& other) noexcept = delete;	// Prevent Move Assignment

			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;
			unsigned int GetVertexCount() const;
			std::vector<float> GetPosition() const;
			void SetPosition(float x, float y, float z);
			std::vector<float> GetRotation() const;
			void SetRotation(float pitch, float yaw, float roll);
			std::vector<float> GetScale() const;
			void SetScale(float x, float y, float z);

		private:
			class OpenGLRenderableObjectImpl;
			OpenGLRenderableObjectImpl* m_pOpenGLRenderableObjectImpl;
		};
	}
}


#endif // ENVIRONMENT__RENDERABLE_OBJECT__HPP