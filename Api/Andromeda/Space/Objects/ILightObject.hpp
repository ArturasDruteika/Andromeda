#ifndef API__OBJECTS__I_LIGHT_OBJECT__HPP
#define API__OBJECTS__I_LIGHT_OBJECT__HPP


#include "IObject.hpp"


namespace Andromeda
{
	class ILightObject
		: public virtual IObject
	{
	public:
		virtual ~ILightObject() = default;
	};
}


#endif // API__OBJECTS__I_LIGHT_OBJECT__HPP