#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#include "../../Colors/include/Colors.hpp"
#include "../../Coordinates/include/Points.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
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
