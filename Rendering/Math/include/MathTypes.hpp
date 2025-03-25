#ifndef RENDERING__MATH_TYPES__HPP
#define RENDERING__MATH_TYPES__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		struct Vec2
		{
			float x;
			float y;
		};

		struct Vec3
		{
			float x;
			float y;
			float z;
		};

		struct Vec4
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct Mat2
		{
			std::array<std::array<float, 2>, 2> data;
		};

		struct Mat3
		{
			std::array<std::array<float, 3>, 3> data;
		};

		struct Mat4
		{
			std::array<std::array<float, 4>, 4> data;
		};
	}
}


#endif // RENDERING__MATH_TYPES__HPP