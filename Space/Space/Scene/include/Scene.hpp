#ifndef SPACE__SCENE__SCENE__HPP
#define SPACE__SCENE__SCENE__HPP


#include "CameraHandler.hpp"
#include "SceneEnvironment.hpp"
#include "SceneLighting.hpp"
#include "SceneObjects.hpp"
#include "SceneState.hpp"
#include "Andromeda/Space/Scene/IScene.hpp"


namespace Andromeda::Space
{
	class Scene
		: public virtual IScene
		, public CameraHandler
		, public SceneEnvironment
		, public SceneLighting
		, public SceneObjects
		, public SceneState
	{
	public:
		Scene();
		~Scene() override;

		Math::Vec3 GetSceneCenter() const override;

		void ClearScene() override;
		void ResetSceneState() override;

	private:
		Math::Vec3 m_sceneCenter;
	};
}


#endif // API_SCENE__I_SCENE__HPP