#ifndef API__RENDERABLE_OBJECTS__INTERFACES__I_SKYROOM__HPP
#define API__RENDERABLE_OBJECTS__INTERFACES__I_SKYROOM__HPP


#include "IRenderableObject.hpp"


namespace Andromeda
{
	class ISkyroom
		: IRenderableObject
	{
	public:
		virtual ~ISkyroom() = default;

		virtual float GetHalfExtent() = 0;
	};
}


#endif // API__RENDERABLE_OBJECTS__INTERFACES__I_SKYROOM__HPP