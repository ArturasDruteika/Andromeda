#ifndef API__OBJECTS__INTERFACES__I_CUBE__HPP
#define API__OBJECTS__INTERFACES__I_CUBE__HPP


#include "IRenderableObject.hpp"


namespace Andromeda
{
	class ICube
		: IRenderableObject
	{
	public:
		virtual ~ICube() = default;

		virtual float GetHalfExtent() = 0;
	};
}


#endif // API__OBJECTS__INTERFACES__I_CUBE__HPP