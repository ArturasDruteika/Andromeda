#ifndef API__OBJECTS__I_LIGHT_OBJECT__HPP
#define API__OBJECTS__I_LIGHT_OBJECT__HPP


#include "IObject.hpp"
#include "../Light/LightTypes.hpp"


namespace Andromeda
{
	class ILightObject
		: public virtual IObject
	{
	public:
		virtual ~ILightObject() = default;

		// Getters
		virtual const LightType& GetLightType() const = 0;
	};
}


#endif // API__OBJECTS__I_LIGHT_OBJECT__HPP