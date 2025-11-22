#ifndef API__RENDERABLE_OBJECTS__INTERFACES__I_SPHERE__HPP
#define API__RENDERABLE_OBJECTS__INTERFACES__I_SPHERE__HPP


#include "IRenderableObject.hpp"


namespace Andromeda
{
	class ISphere
		: IRenderableObject
	{
	public:
		virtual ~ISphere() = default;

		virtual float GetRadius() = 0;
	};
}


#endif // API__RENDERABLE_OBJECTS__INTERFACES__I_SPHERE__HPP