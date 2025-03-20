#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#include "../../Attributes/include/Points.hpp"
#include "../../Attributes/include/Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		struct Vertex
		{
			Point3D position;
			Color color;
		};
	}
}


#endif // RENDERING__VERTEX__HPP