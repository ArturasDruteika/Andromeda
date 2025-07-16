#ifndef RENDERING__LUMINOUS_BEHAVIOR__HPP
#define RENDERING__LUMINOUS_BEHAVIOR__HPP


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


#include "pch.hpp"
#include "ILightBehavior.hpp"
#include "Light.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API LuminousBehavior
			: public ILightBehavior
		{
		public:
			//LuminousBehavior();
			LuminousBehavior(Light* light);
			~LuminousBehavior();

			Light* GetLight() const;

		private:
			Light* m_light;
		};
	}
}


#endif // RENDERING__LUMINOUS_BEHAVIOR__HPP