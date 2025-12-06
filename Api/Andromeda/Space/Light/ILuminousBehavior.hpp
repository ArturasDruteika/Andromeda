#ifndef ANDROMEDA__LIGHT__I_LUMINOUS_BEHAVIOR__HPP
#define ANDROMEDA__LIGHT__I_LUMINOUS_BEHAVIOR__HPP


#include "ILight.hpp"
#include "ILightBehavior.hpp"
#include "LightTypes.hpp"


namespace Andromeda
{
	class ILuminousBehavior
		: public virtual ILightBehavior
	{
	public:
		virtual ~ILuminousBehavior() = default;

		virtual LightType GetType() const = 0;
		virtual const ILight& GetLight() const = 0;
	};
}


#endif // ANDROMEDA__LIGHT__I_LUMINOUS_BEHAVIOR__HPP