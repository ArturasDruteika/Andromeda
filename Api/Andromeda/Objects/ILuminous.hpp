#ifndef API__OBJECTS__INTERFACES__I_LUMINOUS__HPP
#define API__OBJECTS__INTERFACES__I_LUMINOUS__HPP


#include "Space/Light/Interfaces/include/ILightBehavior.hpp"


namespace Andromeda
{
	class ILuminous
	{
	public:
		virtual ~ILuminous() = default;
		
		// Getters
		virtual bool IsLuminous() const = 0;
		virtual Space::ILightBehavior* GetLightBehavior() const = 0;
		// Setters
		virtual void SetLuminousBehavior(Space::ILightBehavior* behavior) = 0;
	};
}


#endif // API__OBJECTS__INTERFACES__I_LUMINOUS__HPP