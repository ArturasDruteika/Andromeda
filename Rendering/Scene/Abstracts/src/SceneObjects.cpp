#include "../include/SceneObjects.hpp"


namespace Andromeda::Rendering
{
	SceneObjects::SceneObjects() = default;

	SceneObjects::~SceneObjects()
	{
		for (auto& [id, object] : m_objects)
		{
			delete object;
		}
		m_objects.clear();
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
			LuminousBehavior* luminousObject = dynamic_cast<LuminousBehavior*>(object);
			m_luminousObjects.insert({ id, luminousObject });
		}
	}

	void SceneObjects::RemoveObject(int id)
	{
		delete m_objects[id];
		m_objects.erase(id);
	}

	void SceneObjects::AddDirectionaLight(int id, DirectionalLight* pDirectionalLight)
	{
		m_luminousObjects.insert({ id, pDirectionalLight });
	}
}
