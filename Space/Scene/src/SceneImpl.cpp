#include "../include/SceneImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Scene::SceneImpl::SceneImpl()
		{
		}

		Scene::SceneImpl::~SceneImpl()
		{
		}

		void Scene::SceneImpl::AddObject(int id, ObjectBase* pObj)
		{
			m_objectsMap[id] = pObj;
		}

		void Scene::SceneImpl::RemoveObject(int id)
		{
			delete m_objectsMap[id];
			m_objectsMap[id] = nullptr;
			m_objectsMap.erase(id);
		}
	}
}
