#ifndef SCENE__SCENE__HPP
#define SCENE__SCENE__HPP


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
#include "../../RenderableObjects/include/OpenGLRenderableObject.hpp"


namespace Andromeda
{
	namespace Scene
	{
		class SCENE_API OpenGLScene
		{
		public:
			OpenGLScene();
			~OpenGLScene();

			OpenGLScene(const OpenGLScene& other) = delete;	// Prevent Copy Constructor
			OpenGLScene& operator=(const OpenGLScene& other) = delete;	// Prevent Copy Assignment
			OpenGLScene(OpenGLScene&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLScene& operator=(OpenGLScene&& other) noexcept = delete;	// Prevent Move Assignment

			void AddObject(OpenGLRenderableObject* object);
			void RemoveObject(OpenGLRenderableObject* object);
			const std::vector<OpenGLRenderableObject*> GetObjects() const;

		private:
			class OpenGLSceneImpl;
			OpenGLSceneImpl* m_pOpenGLSceneImpl;
		};
	}
}


#endif // SCENE__SCENE__HPP