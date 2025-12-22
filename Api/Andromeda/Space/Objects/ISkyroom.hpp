#ifndef API__OBJECTS__I_SKYROOM__HPP
#define API__OBJECTS__I_SKYROOM__HPP


#include "IGeometricObject.hpp"
#include "ISurfaceObject.hpp"


namespace Andromeda
{
	class ISkyroom
		: public virtual IGeometricObject
		, public virtual ISurfaceObject
	{
	public:
		virtual ~ISkyroom() = default;

		// Getters
		virtual float GetHalfExtent() const = 0;
		// Setters
		virtual void SetHalfExtent(float halfExtent) = 0;
	};
}


#endif // API__OBJECTS__I_SKYROOM__HPP