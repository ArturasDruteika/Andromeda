#ifndef ENVIRONMENT__I_SCENE_STATE__HPP
#define ENVIRONMENT__I_SCENE_STATE__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ISceneState
	{
	public:
		virtual ~ISceneState();

		virtual bool StateChanged(const std::unordered_map<int, IRenderableObject*>& objects) const = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_STATE__HPP