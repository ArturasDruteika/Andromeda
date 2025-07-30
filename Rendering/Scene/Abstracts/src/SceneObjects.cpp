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

	void SceneObjects::AddObject(int id, IRenderableObject* object)
	{
		m_objects.insert({ id, object });
	}

	void SceneObjects::RemoveObject(int id)
	{
		delete m_objects[id];
		m_objects.erase(id);
	}
}
