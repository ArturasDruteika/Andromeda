#include "../include/SceneObjects.hpp"


namespace Andromeda::Space
{
	SceneObjects::SceneObjects()
		: m_objects{}
	{
	}

	SceneObjects::~SceneObjects()
	{
		for (const auto& [id, object] : m_objects)
		{
			delete object;
		}
	}

	const std::unordered_map<int, IGeometricObject*>& SceneObjects::GetObjects() const
	{
		return m_objects;
	}

	void SceneObjects::AddObject(int id, IGeometricObject* object)
	{
		m_objects[id] = object;
	}

	void SceneObjects::RemoveObject(int id)
	{
		auto it = m_objects.find(id);
		if (it != m_objects.end())
		{
			delete it->second;
			m_objects.erase(it);
		}
	}
}