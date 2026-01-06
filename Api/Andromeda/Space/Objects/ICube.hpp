#ifndef API__OBJECTS__INTERFACES__I_CUBE__HPP
#define API__OBJECTS__INTERFACES__I_CUBE__HPP


#include "IGeometricObject.hpp"
#include "ISurfaceObject.hpp"


namespace Andromeda
{
	class ICube
		: public virtual IGeometricObject
		, public virtual ISurfaceObject
	{
	public:
		virtual ~ICube() = default;

		virtual float GetHalfExtent() const = 0;
	};
}


#endif // API__OBJECTS__INTERFACES__I_CUBE__HPP