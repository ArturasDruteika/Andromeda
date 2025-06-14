#include "../include/ILuminousObjectOpenGL.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		ILuminousObjectOpenGL::~ILuminousObjectOpenGL() = default;

		bool ILuminousObjectOpenGL::IsEmitingLight()
		{
			return true;
		}
	}
}
