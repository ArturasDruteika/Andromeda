#include "../include/OpenGLScene.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLScene::OpenGLScene()
		{
		}

		OpenGLScene::~OpenGLScene()
		{
		}

		void OpenGLScene::AddObject(int id, OpenGLRenderableObject* object)
		{
			m_renderableObjsPtrsMap.insert({ id, object });
		}

		void OpenGLScene::RemoveObject(int id)
		{
			delete m_renderableObjsPtrsMap[id];
			m_renderableObjsPtrsMap.erase(id);
		}

		const std::unordered_map<int, OpenGLRenderableObject*> OpenGLScene::GetObjects() const
		{
			return m_renderableObjsPtrsMap;
		}
	}
}
