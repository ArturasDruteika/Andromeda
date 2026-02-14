#ifndef ANDROMEDA__LIGHT__LIGHT_TYPES__HPP
#define ANDROMEDA__LIGHT__LIGHT_TYPES__HPP


namespace Andromeda
{
	enum class LightType : int
	{
		None = 0,
		Directional = 1,
		Point = 2,
		Spot = 3
	};
}


#endif // ANDROMEDA__LIGHT__LIGHT_TYPES__HPP