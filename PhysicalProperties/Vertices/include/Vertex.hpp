#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#include "../../Colors/include/Colors.hpp"
#include "../../Space/include/Points.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::PhysicalProperties
{
	struct Vertex
	{
		Point3D position;
		Color color;
		Math::Vec3 normal;

		Vertex() = default;

		Vertex(const Point3D& pos, const Color& col)
			: position(pos)
			, color(col)
			, normal(0.0f, 0.0f, 0.0f)
		{
		}

		Vertex(const Point3D& pos, const Color& col, const Math::Vec3& normal)
			: position(pos)
			, color(col)
			, normal(normal)
		{
		}

		bool operator==(const Vertex& other) const
		{
			return position == other.position &&
				color == other.color &&
				normal == other.normal;
		}
	};
}

#endif // RENDERING__VERTEX__HPP
