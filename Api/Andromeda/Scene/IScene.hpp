#ifndef API__SCENE__I_SCENE__HPP
#define API__SCENE__I_SCENE__HPP


#include "ICameraHandler.hpp"
#include "ISceneEnvironment.hpp"
#include "ISceneLighting.hpp"
#include "ISceneObjects.hpp"
#include "ISceneState.hpp"


namespace Andromeda
{
	class IScene
		: public ICameraHandler
		, public ISceneEnvironment
		, public ISceneLighting
		, public ISceneObjects
		, public ISceneState
	{
	public:
		virtual ~IScene() = default;

		virtual Math::Vec3 GetSceneCenter() const = 0;

		virtual void ClearScene() = 0;
		virtual void ResetSceneState() = 0;
	};
}


#endif // API_SCENE__I_SCENE__HPP