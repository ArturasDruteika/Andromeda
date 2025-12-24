#include "../include/SceneObjects.hpp"


namespace Andromeda::Space
{
	SceneObjects::SceneObjects()
		: m_objects{}
		, m_luminousObjects{}
	{
	}

	SceneObjects::~SceneObjects()
	{
		for (const auto& [id, object] : m_objects)
		{
			delete object;
		}
		for (const auto& [id, lightObject] : m_luminousObjects)
		{
			delete lightObject;
		}
	}

	const std::unordered_map<int, IGeometricObject*>& SceneObjects::GetObjects() const
	{
		return m_objects;
	}

	void SceneObjects::AddObject(int id, IGeometricObject* object)
	{
		m_objects[id] = object;
		if (dynamic_cast<ILightObject*>(object) != nullptr)
		{
			m_luminousObjects[id] = dynamic_cast<ILightObject*>(object);
		}
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

	void SceneObjects::AddLightObject(int id, ILightObject* pLightObject)
	{
		m_luminousObjects[id] = pLightObject;
	}
}