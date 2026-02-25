#ifndef API__SCENE__I_SCENE_UPDATE_HOOKS__HPP
#define API__SCENE__I_SCENE_UPDATE_HOOKS__HPP


#include "IUpdateHooks.hpp"


namespace Andromeda
{
	class ISceneUpdateHooks
		: public virtual IUpdateHooks
	{
	public:
		using Callback = IUpdateHooks::Callback;
		using Handle = IUpdateHooks::Handle;

		~ISceneUpdateHooks() override = default;
	};
}


#endif // API__SCENE__I_SCENE_UPDATE_HOOKS__HPP

