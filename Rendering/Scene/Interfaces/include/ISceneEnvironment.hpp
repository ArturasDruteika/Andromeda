#ifndef ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP
#define ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ISceneEnvironment
	{
	public:
		virtual ~ISceneEnvironment();

		// Getters
		virtual float GetAmbientStrength() const = 0;
		// Setters
		virtual void SetAmbientStrength(float ambientStrength) = 0;

		virtual void ResizeGrid(float resizeFactor) = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP