#include "../include/SceneState.hpp"


namespace Andromeda::Space
{
	SceneState::SceneState() = default;

	SceneState::~SceneState() = default;

	bool SceneState::StateChanged(const std::unordered_map<int, IGeometricObject*>& objects) const
	{
		for (const auto& [id, object] : objects)
		{
			if (object->StateChanged())
			{
				return true;
			}
		}
		return false;
	}
}