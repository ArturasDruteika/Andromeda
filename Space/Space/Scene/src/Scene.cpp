#include "../include/Scene.hpp"


namespace Andromeda::Space
{
	Scene::Scene()
		: CameraHandler{}
		, SceneEnvironment{}
		, SceneLighting{}
		, SceneObjects{}
		, SceneState{}
		, m_sceneCenter{ Math::Vec3{ 0.0f } }
	{
	}

	Scene::~Scene()
	{
		ClearScene();
	}

	void Scene::AddObject(int id, IGeometricObject* object)
	{
		SceneObjects::AddObject(id, object);
		if (dynamic_cast<ILightObject*>(object))
		{
			const ILightObject* lightObject = dynamic_cast<const ILightObject*>(object);
			AddLightObject(id, lightObject);
		}
	}

	void Scene::RemoveObject(int id)
	{
		SceneObjects::RemoveObject(id);
		if (dynamic_cast<ILightObject*>(m_objects[id]))
		{
			RemoveLightObject(id);
		}
	}

	Math::Vec3 Scene::GetSceneCenter() const
	{
		return m_sceneCenter;
	}

	void Scene::ClearScene()
	{
		for (const auto& [id, object] : m_objects)
		{
			delete object;
		}
		m_objects.clear();
		for (const auto& [id, light] : m_directionalLights)
		{
			delete light;
		}
		m_directionalLights.clear();
		for (const auto& [id, light] : m_pointLights)
		{
			delete light;
		}
		m_pointLights.clear();
		for (const auto& [id, lightObject] : m_lightObjects)
		{
			delete lightObject;
		}
		m_lightObjects.clear();
	}

	void Scene::ResetSceneState()
	{
	}
}