#ifndef API__OBJECTS__I_SKYROOM__HPP
#define API__OBJECTS__I_SKYROOM__HPP


#include "IGeometricObject.hpp"


namespace Andromeda
{
	class ISkyroom
		: IGeometricObject
	{
	public:
		virtual ~ISkyroom() = default;

		virtual float GetHalfExtent() = 0;
	};
}


#endif // API__OBJECTS__I_SKYROOM__HPP