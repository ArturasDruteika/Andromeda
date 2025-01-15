#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Environment
	{
		OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
		{
		}

		OpenGLScene::OpenGLSceneImpl::~OpenGLSceneImpl()
		{
		}

		void OpenGLScene::OpenGLSceneImpl::AddObject(int id, OpenGLRenderableObject* object)
		{
			m_renderableObjsPtrsMap.insert({ id, object });
		}

		void OpenGLScene::OpenGLSceneImpl::RemoveObject(int id)
		{
			delete m_renderableObjsPtrsMap[id];
			m_renderableObjsPtrsMap.erase(id);
		}

		const std::unordered_map<int, OpenGLRenderableObject*> OpenGLScene::OpenGLSceneImpl::GetObjects() const
		{
			return m_renderableObjsPtrsMap;
		}
	}
}
