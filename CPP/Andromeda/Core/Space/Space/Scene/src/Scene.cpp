#include "../include/Scene.hpp"
#include "../../Transformations/include/Transformable.hpp"
#include "../../SceneGraph/include/ObjectComponent.hpp"
#include "../../SceneGraph/include/LightComponent.hpp"


namespace Andromeda::Space
{
	Scene::Scene()
		: CameraHandler{}
		, SceneEnvironment{}
		, SceneLighting{}
		, SceneObjects{}
		, SceneState{}
		, m_sceneCenter{ Math::Vec3{ 0.0f } }
		, m_rootNode{ std::make_unique<SceneNode>(std::make_unique<Transformable>()) }
	{
	}

	Scene::~Scene()
	{
		ClearScene();
	}

	void Scene::AttachNode(std::unique_ptr<SceneNode> node)
	{
		if (!node)
		{
			return;
		}

		SceneNode* nodePtr = node.get();
		m_rootNode->AttachChild(std::move(node));

		if (nodePtr)
		{
			RegisterNodeRecursive(*nodePtr);
		}
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
		std::unordered_map<int, IGeometricObject*>::const_iterator it = m_objects.find(id);
		if (it != m_objects.end())
		{
			if (dynamic_cast<const ILightObject*>(it->second))
			{
				RemoveLightObject(id);
			}
		}
		SceneObjects::RemoveObject(id);
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
		// Update scene state based on deltaTime
	}

	void Scene::RegisterNode(SceneNode& node)
	{
		node.ForEachComponent(
			[this, &node](ISceneComponent& component)
			{
				ObjectComponent* objComponent = dynamic_cast<ObjectComponent*>(&component);
				if (!objComponent)
				{
					LightComponent* lightComponent = dynamic_cast<LightComponent*>(&component);
					if (!lightComponent)
					{
						return;
					}

					const ILightObject* lightObject = lightComponent->GetLightObject();
					if (!lightObject)
					{
						return;
					}

					AddLightObject(lightComponent->GetId(), lightObject);
					return;
				}

				IGeometricObject* object = objComponent->GetObject();
				if (!object)
				{
					return;
				}

				AddObject(objComponent->GetId(), object);
				SetObjectTransform(objComponent->GetId(), &node.GetTransform());
			});
	}

	void Scene::RegisterNodeRecursive(SceneNode& node)
	{
		RegisterNode(node);

		node.ForEachChild(
			[this](ISceneNode& child)
			{
				SceneNode* childNode = dynamic_cast<SceneNode*>(&child);
				if (childNode)
				{
					RegisterNodeRecursive(*childNode);
				}
			});
	}
}