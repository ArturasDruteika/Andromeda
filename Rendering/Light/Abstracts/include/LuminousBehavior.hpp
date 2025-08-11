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
#include "../../Interfaces/include/ILightBehavior.hpp"
#include "../../Support/include/LightTypes.hpp"
#include "Light.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API LuminousBehavior
			: public ILightBehavior
		{
		public:
			LuminousBehavior(Light* light, const LightType& type);
			~LuminousBehavior();

			LightType GetType() const;
			Light* GetLight() const;

		private:
			LightType m_type;
			Light* m_light;
		};
	}
}


#endif // RENDERING__LUMINOUS_BEHAVIOR__HPP