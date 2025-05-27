#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#include "Points.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		struct Vertex
		{
			Space::Point3D position;
			Space::Color color;
			Math::Vec3 normal;

			Vertex() = default;

			Vertex(const Space::Point3D& pos, const Space::Color& col)
				: position(pos)
				, color(col)
				, normal(0.0f, 0.0f, 0.0f)
			{
			}

			Vertex(const Space::Point3D& pos, const Space::Color& col, const Math::Vec3& normal)
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
}

#endif // RENDERING__VERTEX__HPP
