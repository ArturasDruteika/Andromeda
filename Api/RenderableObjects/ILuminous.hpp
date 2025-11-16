#ifndef API__RENDERABLE_OBJECTS__INTERFACES__I_LUMINOUS__HPP
#define API__RENDERABLE_OBJECTS__INTERFACES__I_LUMINOUS__HPP


#include "ILightBehavior.hpp"


namespace Andromeda
{
	class ILuminous
	{
	public:
		virtual ~ILuminous() = default;
		
		// Getters
		virtual bool IsLuminous() const = 0;
		virtual PhysicalProperties::ILightBehavior* GetLightBehavior() const = 0;
		// Setters
		virtual void SetLuminousBehavior(PhysicalProperties::ILightBehavior* behavior) = 0;
	};
}


#endif // API__RENDERABLE_OBJECTS__INTERFACES__I_LUMINOUS__HPP