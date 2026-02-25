#include "../include/SceneNodeManager.hpp"
#include "../../Transformations/include/Transformable.hpp"
#include "../../SceneGraph/include/ObjectComponent.hpp"
#include "../../SceneGraph/include/LightComponent.hpp"


namespace Andromeda::Space
{
	SceneNodeManager::SceneNodeManager()
		: m_rootNode{ std::make_unique<SceneNode>(std::make_unique<Transformable>()) }
	{
	}

	SceneNodeManager::~SceneNodeManager() = default;

	void SceneNodeManager::AttachNode(std::unique_ptr<ISceneNode> node)
	{
		SceneNode* concreteNode = dynamic_cast<SceneNode*>(node.get());
		if (!concreteNode)
		{
			return;
		}
		AttachNode(std::unique_ptr<SceneNode>(static_cast<SceneNode*>(node.release())));
	}

	void SceneNodeManager::AttachNode(std::unique_ptr<SceneNode> node)
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

	void SceneNodeManager::AddObject(int id, IGeometricObject* object)
	{
		SceneObjects::AddObject(id, object);
		if (dynamic_cast<ILightObject*>(object))
		{
			const ILightObject* lightObject = dynamic_cast<const ILightObject*>(object);
			AddLightObject(id, lightObject);
		}
	}

	void SceneNodeManager::RemoveObject(int id)
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

	void SceneNodeManager::RegisterNode(SceneNode& node)
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

	void SceneNodeManager::RegisterNodeRecursive(SceneNode& node)
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