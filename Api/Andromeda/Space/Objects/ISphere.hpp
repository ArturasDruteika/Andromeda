#ifndef API__OBJECTS__I_SPHERE__HPP
#define API__OBJECTS__I_SPHERE__HPP


#include "IGeometricObject.hpp"


namespace Andromeda
{
	class ISphere
		: IGeometricObject
	{
	public:
		virtual ~ISphere() = default;

		virtual float GetRadius() = 0;
	};
}


#endif // API__OBJECTS__I_SPHERE__HPP