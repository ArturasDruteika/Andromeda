#ifndef API__OBJECTS__INTERFACES__I_CUBE__HPP
#define API__OBJECTS__INTERFACES__I_CUBE__HPP


#include "IGeometricObject.hpp"


namespace Andromeda
{
	class ICube
		: IGeometricObject
	{
	public:
		virtual ~ICube() = default;

		virtual float GetHalfExtent() = 0;
	};
}


#endif // API__OBJECTS__INTERFACES__I_CUBE__HPP