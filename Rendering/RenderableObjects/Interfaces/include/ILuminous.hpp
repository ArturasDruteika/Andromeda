#ifndef RENDERING__INTERFACES__I_LUMINOUS__HPP
#define RENDERING__INTERFACES__I_LUMINOUS__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif

#include "../../../Light/include/ILightBehavior.hpp"


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