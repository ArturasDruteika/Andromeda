#ifndef RENDERING__RAY__HPP
#define RENDERING__RAY__HPP


#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		struct Ray
		{
			glm::vec3 orgigin;
			glm::vec3 direction;
		};
	}
}


#endif // RENDERING__RAY__HPP