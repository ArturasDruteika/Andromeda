#ifndef RENDERING__I_LUMINOUS_OBJECT_OPEN_GL__HPP
#define RENDERING__I_LUMINOUS_OBJECT_OPEN_GL__HPP



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
		class RENDERING_API ILuminousObjectOpenGL
			: public IRenderableObjectOpenGL
		{	
		public:
			virtual ~ILuminousObjectOpenGL();

			// Getters
			virtual bool IsEmitingLight();
			virtual float GetAttenuationConstant() const = 0;
			virtual float GetAttenuationLinear() const = 0;
			virtual float GetAttenuationQuadratic() const = 0;
			// Setters
			
		};
	}
}


#endif // RENDERING__I_LUMINOUS_OBJECT_OPEN_GL__HPP