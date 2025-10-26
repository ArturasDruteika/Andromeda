#include "../include/SceneObjects.hpp"


namespace Andromeda::Rendering
{
	SceneObjects::SceneObjects() = default;

	SceneObjects::~SceneObjects()
	{
		for (auto& [id, object] : m_objects)
		{
			if (object->IsLuminous())
			{
				m_luminousObjects.erase(id);
			}
			delete object;
		}
		m_objects.clear();

		for (auto& [id, object] : m_luminousObjects)
		{
			delete object;
		}
		m_luminousObjects.clear();
	};

	const std::unordered_map<int, IRenderableObject*>& SceneObjects::GetObjects() const
	{
		return m_objects;
	}

	void SceneObjects::AddObject(int id, IRenderableObject* object)
	{
		m_objects.insert({ id, object });
		if (object->IsLuminous())
		{
			AddLuminousObject(id, dynamic_cast<LuminousBehavior*>(object->GetLightBehavior()));
		}
	}

	void SceneObjects::RemoveObject(int id)
	{
		if (m_objects[id]->IsLuminous())
		{
			m_luminousObjects.erase(id);
		}
		delete m_objects[id];
		m_objects.erase(id);
	}

	void SceneObjects::AddLuminousObject(int id, LuminousBehavior* pLuminousObject)
	{
		m_luminousObjects.insert({ id, pLuminousObject });
	}
}
