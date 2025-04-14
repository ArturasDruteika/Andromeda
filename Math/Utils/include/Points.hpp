#ifndef LINEAR_ALGEBRA__POINTS__HPP
#define LINEAR_ALGEBRA__POINTS__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Math
	{
		struct Point2D
		{
			float x;
			float y;
			Point2D(float x, float y) : x(x), y(y) {}
			static constexpr int Size()
			{
				return sizeof(Point2D) / sizeof(float);
			}
		};

		struct Point3D
		{
			float x;
			float y;
			float z;
			Point3D(float x, float y, float z) : x(x), y(y), z(z) {}
			static constexpr int Size()
			{
				return sizeof(Point3D) / sizeof(float);
			}
		};
	}
}

#endif // LINEAR_ALGEBRA__POINTS__HPP
