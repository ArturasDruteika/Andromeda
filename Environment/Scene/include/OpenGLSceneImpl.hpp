	#ifndef ENVIRONMENT__SCENE_IMPL__HPP
	#define ENVIRONMENT__SCENE_IMPL__HPP


	#include "../include/OpenGLScene.hpp"
	#include "../../RenderableObjects/include/OpenGLRenderableObject.hpp"


	namespace Andromeda
	{
		namespace Environment
		{
			class OpenGLScene::OpenGLSceneImpl
			{
			public:
				OpenGLSceneImpl();
				~OpenGLSceneImpl();

				OpenGLSceneImpl(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Constructor
				OpenGLSceneImpl& operator=(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Assignment
				OpenGLSceneImpl(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Constructor
				OpenGLSceneImpl& operator=(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Assignment

				void AddObject(int id, OpenGLRenderableObject* object);
				void RemoveObject(int id);
				const std::unordered_map<int, OpenGLRenderableObject*> GetObjects() const;

			private:
				std::unordered_map<int, OpenGLRenderableObject*> m_renderableObjsPtrsMap;
			};
		}
	}


	#endif // SCENE__SCENE_IMPL__HPP