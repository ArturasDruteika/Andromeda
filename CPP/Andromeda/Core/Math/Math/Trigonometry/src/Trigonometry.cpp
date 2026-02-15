#include "../include/Trigonometry.hpp"
#include "../../Constants/include/Constants.hpp"


namespace Andromeda::Math
{
	float Trigonometry::Deg2Rad(float deg)
	{
		return deg * (Math::PI / 180.0f);
	}

	float Trigonometry::Rad2Deg(float rad)
	{
		return rad * (180.0f / Math::PI);
	}
}
