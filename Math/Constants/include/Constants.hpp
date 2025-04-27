#ifndef MATH__CONSTANTS__HPP
#define MATH__CONSTANTS__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Math
	{
		constexpr float PI = 3.14159265358979323846f;
		constexpr float EPSILON = 1e-6f; // Small value for floating-point comparisons
		constexpr float INFINITY_VALUE = std::numeric_limits<float>::infinity();
		constexpr float NEGATIVE_INFINITY_VALUE = -std::numeric_limits<float>::infinity();
	}
}

#endif // MATH__CONSTANTS__HPP
