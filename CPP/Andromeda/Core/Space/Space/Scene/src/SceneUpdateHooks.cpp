#include "../include/SceneUpdateHooks.hpp"


namespace Andromeda::Space
{
	SceneUpdateHooksManager::SceneUpdateHooksManager() = default;

	SceneUpdateHooksManager::~SceneUpdateHooksManager() = default;

	SceneUpdateHooksManager::Handle SceneUpdateHooksManager::AddUpdateCallback(Callback callback)
	{
		return m_updateHooks.Add(std::move(callback));
	}

	void SceneUpdateHooksManager::RemoveUpdateCallback(Handle handle)
	{
		m_updateHooks.Remove(handle);
	}

	void SceneUpdateHooksManager::ClearUpdateCallbacks()
	{
		m_updateHooks.Clear();
	}

	void SceneUpdateHooksManager::RunUpdateCallbacks(float deltaTime)
	{
		m_updateHooks.Run(deltaTime);
	}
}
