#include "../include/SceneState.hpp"


namespace Andromeda::Rendering
{
	SceneState::SceneState()
		: m_stateChanged{ false }
	{
	}

	SceneState::~SceneState() = default;

	bool SceneState::StateChanged() const
	{
		return m_stateChanged;
	}

	void SceneState::ResetState()
	{
		m_stateChanged = false;
	}
}
