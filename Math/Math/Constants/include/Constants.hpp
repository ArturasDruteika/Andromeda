#ifndef MATH__CONSTANTS__HPP
#define MATH__CONSTANTS__HPP


#include "../../LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include <limits>


namespace Andromeda::Math
{
	constexpr float PI = 3.14159265358979323846f;
	constexpr float PI_HALF = PI / 2.0f;
	constexpr float EPSILON = 1e-6f; // Small value for floating-point comparisons
	constexpr float INFINITY_VALUE = std::numeric_limits<float>::infinity();
	constexpr float NEGATIVE_INFINITY_VALUE = -std::numeric_limits<float>::infinity();

	constexpr Math::Vec3 X_AXIS{ 1.0f, 0.0f, 0.0f };
	constexpr Math::Vec3 Y_AXIS{ 0.0f, 1.0f, 0.0f };
	constexpr Math::Vec3 NEGATIVE_Z_AXIS{ 0.0f, 0.0f, -1.0f };
}

#endif // MATH__CONSTANTS__HPP
