#ifndef API__OBJECTS__I_SKYROOM__HPP
#define API__OBJECTS__I_SKYROOM__HPP


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


#endif // API__OBJECTS__I_SKYROOM__HPP