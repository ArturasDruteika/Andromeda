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
	}
}
