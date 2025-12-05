#ifndef ANDROMEDA__LIGHT__I_NON_LUMINOUS_BEHAVIOR_HPP
#define ANDROMEDA__LIGHT__I_NON_LUMINOUS_BEHAVIOR_HPP


#include "ILightBehavior.hpp"
#include "../Materials/IMaterial.hpp"


namespace Andromeda
{
	class INonLuminousBehavior
		: public virtual ILightBehavior
	{
	public:
		virtual ~INonLuminousBehavior() = default;

		// Getters
		virtual const IMaterial& GetMaterial() const = 0;
		// Setters
		virtual void SetMaterial(const IMaterial& material) = 0;
	};
}


#endif // ANDROMEDA__LIGHT__I_NON_LUMINOUS_BEHAVIOR_HPP