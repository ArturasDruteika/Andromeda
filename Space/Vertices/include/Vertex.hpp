#ifndef SPACE__VERTEX__HPP
#define SPACE__VERTEX__HPP


#include "../../Attributes/include/Colors.hpp"
#include "../../DataTypes/include/Points.hpp"


namespace Andromeda
{
	namespace Space
	{
		struct Vertex
		{
			Point3D position;
			Color color;

			Vertex() = default;

			Vertex(const Point3D& pos, const Color& col)
				: position(pos), color(col)
			{
			}

			bool operator==(const Vertex& other) const
			{
				return position == other.position && color == other.color;
			}
		};
	}
}


#endif // SPACE__VERTEX__HPP