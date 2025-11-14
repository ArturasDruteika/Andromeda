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
			PhysicalProperties::Point3D position;
			PhysicalProperties::Color color;
			Math::Vec3 normal;

			Vertex() = default;

			Vertex(const PhysicalProperties::Point3D& pos, const PhysicalProperties::Color& col)
				: position(pos)
				, color(col)
				, normal(0.0f, 0.0f, 0.0f)
			{
			}

			Vertex(const PhysicalProperties::Point3D& pos, const PhysicalProperties::Color& col, const Math::Vec3& normal)
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
