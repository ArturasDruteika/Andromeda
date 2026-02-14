#ifndef SPACE__SCENE__SCENE_STATE__HPP
#define SPACE__SCENE__SCENE_STATE__HPP


#include "../../Objects/include/GeometricObject.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneState.hpp"


namespace Andromeda::Space
{
	class SPACE_API SceneState
		: public virtual ISceneState
	{
	public:
		SceneState();
		~SceneState() override;

		bool StateChanged(const std::unordered_map<int, IGeometricObject*>& objects) const override;
	};
}


#endif // SPACE__SCENE__SCENE_STATE__HPP