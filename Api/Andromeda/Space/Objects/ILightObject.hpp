#ifndef API__OBJECTS__I_LIGHT_OBJECT__HPP
#define API__OBJECTS__I_LIGHT_OBJECT__HPP


#include "IObjecthpp"
#include "ITransformable.hpp"
#include "ILuminous.hpp"


namespace Andromeda
{
	class ILightObject
	{
	public:
		virtual ~ILightObject();
	};
}


#endif // API__OBJECTS__I_LIGHT_OBJECT__HPP