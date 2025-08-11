#include "../include/Scene.hpp"


namespace Andromeda::Rendering
{
	Scene::Scene()
		: m_sceneCenter{ glm::vec3(0.0f, 0.0f, 0.0f) }
	{

	};

	Scene::~Scene() = default;

	glm::vec3 Scene::GetSceneCenter() const
	{
		return m_sceneCenter;
	}
}
