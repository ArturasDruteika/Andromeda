#include "../include/Scene.hpp"
#include "../include/SceneImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Scene::Scene()
			: m_pSceneImpl{ new Scene::SceneImpl() }
		{
		}

		Scene::~Scene()
		{
			delete m_pSceneImpl;
		}

		void Scene::AddObject(int id, ObjectBase* pObj)
		{
			m_pSceneImpl->AddObject(id, pObj);
		}

		void Scene::RemoveObject(int id)
		{
			m_pSceneImpl->RemoveObject(id);
		}
	}
}
