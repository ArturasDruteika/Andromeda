#ifndef SCENE__RENDERABLE_OBJECT__HPP
#define SCENE__RENDERABLE_OBJECT__HPP


#if defined(_WIN32)
	#if defined(SCENE_EXPORT)
		#define SCENE_API __declspec(dllexport)
	#else
		#define SCENE_API __declspec(dllimport)
	#endif /* SCENE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define SCENE_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"


namespace Andromeda
{
	namespace Scene
	{
		class SCENE_API OpenGLRenderableObject
		{
		public:
			OpenGLRenderableObject(const std::vector<float>& vertices);
			~OpenGLRenderableObject();

			OpenGLRenderableObject(const OpenGLRenderableObject& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderableObject& operator=(const OpenGLRenderableObject& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderableObject(OpenGLRenderableObject&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderableObject& operator=(OpenGLRenderableObject&& other) noexcept = delete;	// Prevent Move Assignment

			void SetPosition(float x, float y, float z);
			std::vector<float> GetPosition();
			void SetRotation(float pitch, float yaw, float roll);
			std::vector<float> GetRotation();
			void SetScale(float x, float y, float z);
			std::vector<float> GetScale();

		private:
			class OpenGLRenderableObjectImpl;
			OpenGLRenderableObjectImpl* m_pOpenGLRenderableObjectImpl;
		};
	}
}


#endif // SCENE__RENDERABLE_OBJECT__HPP