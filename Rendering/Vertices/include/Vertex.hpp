#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#include "Points.hpp"
#include "Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		struct Vertex
		{
			Space::Point3D position;
			Space::Color color;

			Vertex() = default;

			Vertex(const Space::Point3D& pos, const Space::Color& col)
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


#endif // RENDERING__VERTEX__HPP