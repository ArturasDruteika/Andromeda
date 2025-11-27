#ifndef SPACE__LIGHT_TYPES__HPP
#define SPACE__LIGHT_TYPES__HPP


namespace Andromeda::Space
{
	enum class LightType : int
	{
		None = 0,
		Directional = 1,
		Point = 2,
		Spot = 3
	};
}


#endif // SPACE__LIGHT_TYPES__HPP