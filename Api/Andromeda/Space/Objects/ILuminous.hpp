#ifndef API__OBJECTS__I_LUMINOUS__HPP
#define API__OBJECTS__I_LUMINOUS__HPP


#include "../Light/ILightBehavior.hpp"


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


#endif // API__OBJECTS__I_LUMINOUS__HPP