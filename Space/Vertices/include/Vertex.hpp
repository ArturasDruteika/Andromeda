#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#include "../../Attributes/include/Colors.hpp"
#include "Points.hpp"


namespace Andromeda
{
	namespace Space
	{
		struct Vertex
		{
			Space::Point3D position;
			Color color;
		};
	}
}


#endif // RENDERING__VERTEX__HPP