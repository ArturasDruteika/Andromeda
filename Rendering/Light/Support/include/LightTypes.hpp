#ifndef RENDERING__LIGHT_TYPES__HPP
#define RENDERING__LIGHT_TYPES__HPP


#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		enum class LightType : int
		{
			None = 0,
			Directional = 1,
			Point = 2,
			Spot = 3
		};
	}
}


#endif // RENDERING__LIGHT_TYPES__HPP