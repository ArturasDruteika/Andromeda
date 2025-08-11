#ifndef RENDERING__INTERFACES__I_LUMINOUS__HPP
#define RENDERING__INTERFACES__I_LUMINOUS__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../../Light/Interfaces/include/ILightBehavior.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ILuminous
	{
	public:
		virtual ~ILuminous();
		
		// Getters
		virtual bool IsLuminous() const = 0;
		virtual ILightBehavior* GetLightBehavior() const = 0;
		// Setters
		virtual void SetLuminousBehavior(ILightBehavior* behavior) = 0;
	};
}


#endif // RENDERING__INTERFACES__I_LUMINOUS__HPP