#ifndef SPACE__SCENE__SCENE__HPP
#define SPACE__SCENE__SCENE__HPP


#include "CameraHandler.hpp"
#include "SceneEnvironment.hpp"
#include "SceneLighting.hpp"
#include "SceneObjects.hpp"
#include "SceneState.hpp"
#include "SceneUpdateHooks.hpp"
#include "../../SceneGraph/include/SceneNode.hpp"
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
		, public SceneLighting
		, public SceneObjects
		, public SceneState
	{
	public:
		Scene();
		~Scene() override;

		// Scene graph integration
		void AttachNode(std::unique_ptr<SceneNode> node);

		void AddObject(int id, IGeometricObject* object) override;
		void RemoveObject(int id) override;

		// Getters
		const Math::Vec3& GetSceneCenter() const override;

		void ClearScene() override;
		void ResetSceneState() override;
		void Update(float deltaTime) override;

		// Simulation / game-logic hooks
		SceneUpdateHooks::Handle AddUpdateCallback(SceneUpdateHooks::Callback callback);
		void RemoveUpdateCallback(SceneUpdateHooks::Handle handle);
		void ClearUpdateCallbacks();

	private:
		void RegisterNode(SceneNode& node);
		void RegisterNodeRecursive(SceneNode& node);

		Math::Vec3 m_sceneCenter;
		std::unique_ptr<SceneNode> m_rootNode;
		SceneUpdateHooks m_updateHooks;
	};
}


#endif // API_SCENE__I_SCENE__HPP