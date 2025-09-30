#ifndef ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP
#define ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ISceneEnvironment
	{
	public:
		virtual ~ISceneEnvironment();

		// Getters
		virtual float GetAmbientStrength() const = 0;
		virtual glm::vec4 GetBackgroundColor() const = 0;
		// Setters
		virtual void SetAmbientStrength(float ambientStrength) = 0;
		virtual void SetBackgroundColor(glm::vec4 backroundColor) = 0;

		virtual void ResizeGrid(float resizeFactor) = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP