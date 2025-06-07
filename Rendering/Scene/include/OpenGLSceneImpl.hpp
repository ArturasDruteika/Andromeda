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

			// Getters
			const std::unordered_map<int, IRenderableObjectOpenGL*> GetObjects() const;
			const std::unordered_map<int, Math::Vec3> GetLightEmittingObjectsCoords() const;

			void AddObject(int id, IRenderableObjectOpenGL* object);
			void RemoveObject(int id);
			void ResizeGrid(float resizeFactor);

		private:
			float m_gridSpacing;
			std::unordered_map<int, IRenderableObjectOpenGL*> m_renderableObjsPtrsMap;
			std::unordered_map<int, Math::Vec3> m_lightEmittingObjectsCoords;
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP