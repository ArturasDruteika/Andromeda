#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
		{
		}

		OpenGLScene::OpenGLSceneImpl::~OpenGLSceneImpl()
		{
			for (auto& [id, obj] : m_renderableObjsPtrsMap)
			{
				delete obj;
				m_renderableObjsPtrsMap.at(id) = nullptr;
			}
			m_renderableObjsPtrsMap.clear();
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
