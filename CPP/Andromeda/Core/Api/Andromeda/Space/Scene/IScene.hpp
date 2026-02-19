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
		: public virtual ICameraHandler
		, public virtual ISceneEnvironment
		, public virtual ISceneLighting
		, public virtual ISceneObjects
		, public virtual ISceneState
	{
	public:
		virtual ~IScene() = default;

		virtual const Math::Vec3& GetSceneCenter() const = 0;

		virtual void ClearScene() = 0;
		virtual void ResetSceneState() = 0;
		virtual void Update(float deltaTime) = 0;
	};
}


#endif // API_SCENE__I_SCENE__HPP