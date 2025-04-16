#ifndef LINEAR_ALGEBRA__POINTS__HPP
#define LINEAR_ALGEBRA__POINTS__HPP


namespace Andromeda
{
	namespace Space
	{
		struct Point2D
		{
			float x;
			float y;

			Point2D() : x(0.0f), y(0.0f) {}
			Point2D(float x, float y) : x(x), y(y) {}

			bool operator==(const Point2D& other) const
			{
				return x == other.x && y == other.y;
			}

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

			Point3D() : x(0.0f), y(0.0f), z(0.0f) {}
			Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

			bool operator==(const Point3D& other) const
			{
				return x == other.x && y == other.y && z == other.z;
			}

			static constexpr int Size()
			{
				return sizeof(Point3D) / sizeof(float);
			}
		};
	}
}

#endif // LINEAR_ALGEBRA__POINTS__HPP
