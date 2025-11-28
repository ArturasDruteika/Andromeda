#ifndef API__SCENE__I_SCENE_STATE__HPP
#define API__SCENE__I_SCENE_STATE__HPP


#include "../Objects/IGeometricObject.hpp"


namespace Andromeda
{
	class ISceneState
	{
	public:
		virtual ~ISceneState() = default;

		virtual bool StateChanged(const std::unordered_map<int, IGeometricObject*>& objects) const = 0;
	};
}


#endif // API__SCENE__I_SCENE_STATE__HPP