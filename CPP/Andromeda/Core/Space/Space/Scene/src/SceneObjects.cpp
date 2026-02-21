#include "../include/SceneObjects.hpp"


namespace Andromeda::Space
{
	SceneObjects::SceneObjects()
		: m_objects{}
		, m_objectTransforms{}
	{
	}

	SceneObjects::~SceneObjects()
	{
		m_objects.clear();
		m_objectTransforms.clear();
	}

	const std::unordered_map<int, IGeometricObject*>& SceneObjects::GetObjects() const
	{
		return m_objects;
	}

	const std::unordered_map<int, ITransformable*>& SceneObjects::GetObjectTransforms() const
	{
		return m_objectTransforms;
	}

	void SceneObjects::AddObject(int id, IGeometricObject* object)
	{
		m_objects[id] = object;
	}

	void SceneObjects::RemoveObject(int id)
	{
		std::unordered_map<int, IGeometricObject*>::iterator it = m_objects.find(id);
		if (it != m_objects.end())
		{
			m_objects.erase(it);
		}
		m_objectTransforms.erase(id);
	}

	void SceneObjects::SetObjectTransform(int id, ITransformable* transform)
	{
		m_objectTransforms[id] = transform;
	}
}