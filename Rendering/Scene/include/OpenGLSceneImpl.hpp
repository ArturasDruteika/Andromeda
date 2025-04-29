#ifndef ENVIRONMENT__SCENE_IMPL__HPP
#define ENVIRONMENT__SCENE_IMPL__HPP


#include "../include/OpenGLScene.hpp"


namespace Andromeda
{
	namespace Rendering
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

			void AddObject(int id, IRenderableObjectOpenGL* object);
			void RemoveObject(int id);
			const std::unordered_map<int, IRenderableObjectOpenGL*> GetObjects() const;

		private:
			std::unordered_map<int, IRenderableObjectOpenGL*> m_renderableObjsPtrsMap;
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP