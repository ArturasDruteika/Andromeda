#ifndef SPACE__SCENE__SCENE__HPP
#define SPACE__SCENE__SCENE__HPP


#include "CameraHandler.hpp"
#include "SceneEnvironment.hpp"
#include "SceneLighting.hpp"
#include "SceneObjects.hpp"
#include "SceneState.hpp"
#include "SceneNodeManager.hpp"
#include "SceneUpdateHooks.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/IScene.hpp"
#include "pch.hpp"

#include <functional>


namespace Andromeda::Space
{
	class SPACE_API Scene
		: public IScene
		, public CameraHandler
		, public SceneEnvironment
		, public SceneState
		, public SceneNodeManager
		, public SceneUpdateHooksManager
	{
	public:
		Scene();
		~Scene() override;

		// Getters
		const Math::Vec3& GetSceneCenter() const override;

		void ClearScene() override;
		void ResetSceneState() override;
		void Update(float deltaTime) override;

	private:
		Math::Vec3 m_sceneCenter;
	};
}


#endif // API_SCENE__I_SCENE__HPP