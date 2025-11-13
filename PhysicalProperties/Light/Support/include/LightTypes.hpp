#ifndef PHYSICAL_PROPERTIES__LIGHT_TYPES__HPP
#define PHYSICAL_PROPERTIES__LIGHT_TYPES__HPP


#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::PhysicalProperties
{
	enum class LightType : int
	{
		None = 0,
		Directional = 1,
		Point = 2,
		Spot = 3
	};
}


#endif // PHYSICAL_PROPERTIES__LIGHT_TYPES__HPP