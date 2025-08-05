#include "../include/SceneState.hpp"


namespace Andromeda::Rendering
{
	SceneState::SceneState()
	{
	}

	SceneState::~SceneState() = default;

	bool SceneState::StateChanged(const std::unordered_map<int, IRenderableObject*>& objects) const
	{
		for (const auto& [id, obj] : objects)
		{
			if (id >= 0)
			{
				if (obj && obj->StateChanged())
				{
					return true;
				}
			}
		}
		return false;
	}
}
