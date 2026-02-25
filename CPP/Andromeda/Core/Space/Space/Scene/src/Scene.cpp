#include "../include/Scene.hpp"
namespace Andromeda::Space
{
	Scene::Scene()
		: CameraHandler{}
		, SceneEnvironment{}
		, SceneState{}
		, m_sceneCenter{ Math::Vec3{ 0.0f } }
	{
	}

	Scene::~Scene()
	{
		ClearScene();
	}

	const Math::Vec3& Scene::GetSceneCenter() const
	{
		return m_sceneCenter;
	}

	void Scene::ClearScene()
	{
		m_objects.clear();
		m_objectTransforms.clear();
		m_directionalLights.clear();
		m_pointLights.clear();
		m_lightObjects.clear();
	}

	void Scene::ResetSceneState()
	{
	}

	void Scene::Update(float deltaTime)
	{
		RunUpdateCallbacks(deltaTime);
	}

}