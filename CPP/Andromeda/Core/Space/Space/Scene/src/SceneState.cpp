#include "../include/SceneState.hpp"


namespace Andromeda::Space
{
	SceneState::SceneState() = default;

	SceneState::~SceneState() = default;

	bool SceneState::StateChanged(const std::unordered_map<int, IGeometricObject*>& objects) const
	{
		// TODO: Implement state change detection logic based on nodes, not the object itself
		//for (const auto& [id, object] : objects)
		//{
		//	if (object->StateChanged())
		//	{
		//		return true;
		//	}
		//}
		//return false;
		return false;
	}
}