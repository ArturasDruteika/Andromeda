#ifndef LINEAR_ALGEBRA__LINEAR_ALGEBRA_DATA_TYPES__HPP
#define LINEAR_ALGEBRA__LINEAR_ALGEBRA_DATA_TYPES__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Math
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
			Vec2 rows[2];
		};

		struct Mat3
		{
			Vec3 rows[3];
		};

		struct Mat4
		{
			Vec4 rows[4];
		};
	}
}


#endif // LINEAR_ALGEBRA__LINEAR_ALGEBRA_DATA_TYPES__HPP