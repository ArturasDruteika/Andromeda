#ifndef RENDERING__I_NON_LUMINOUS_OBJECT_OPEN_GL__HPP
#define RENDERING__I_NON_LUMINOUS_OBJECT_OPEN_GL__HPP



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
#include "IRenderableObjectOpenGL.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API INonLuminousObjectOpenGL
			: public IRenderableObjectOpenGL
		{
		public:
			virtual ~INonLuminousObjectOpenGL();

			// Getters
			virtual bool IsEmitingLight();
			// Setters
			virtual float GetShininess() const = 0;
			virtual float GetSpecularStrength() const = 0;
			// Setters
			virtual void GetShininess(float shininess) const = 0;
			virtual void GetSpecularStrength(float specularStrength) const = 0;
		};
	}
}


#endif // RENDERING__I_NON_LUMINOUS_OBJECT_OPEN_GL__HPP