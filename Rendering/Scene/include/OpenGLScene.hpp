#ifndef ENVIRONMENT__SCENE__HPP
#define ENVIRONMENT__SCENE__HPP


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
#include "../../RenderableObjects/include/OpenGLRenderableObject.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API OpenGLScene
		{
		public:
			OpenGLScene();
			~OpenGLScene();

			OpenGLScene(const OpenGLScene& other) = delete;	// Prevent Copy Constructor
			OpenGLScene& operator=(const OpenGLScene& other) = delete;	// Prevent Copy Assignment
			OpenGLScene(OpenGLScene&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLScene& operator=(OpenGLScene&& other) noexcept = delete;	// Prevent Move Assignment

			void AddObject(int id, OpenGLRenderableObject* object);
			void RemoveObject(int id);
			const std::unordered_map<int, OpenGLRenderableObject*> GetObjects() const;

		private:
			class OpenGLSceneImpl;
			OpenGLSceneImpl* m_pOpenGLSceneImpl;
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP