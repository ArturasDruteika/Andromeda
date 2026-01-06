#ifndef API__OBJECTS__I_SPHERE__HPP
#define API__OBJECTS__I_SPHERE__HPP


#include "IGeometricObject.hpp"
#include "ISurfaceObject.hpp"


namespace Andromeda
{
	class ISphere
		: public virtual IGeometricObject
		, public virtual ISurfaceObject
	{
	public:
		virtual ~ISphere() = default;

		virtual float GetRadius() const = 0;
	};
}


#endif // API__OBJECTS__I_SPHERE__HPP