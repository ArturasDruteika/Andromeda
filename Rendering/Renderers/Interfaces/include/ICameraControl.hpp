#ifndef RENDERER__I_CAMERA_CONTROL__HPP
#define RENDERER__I_CAMERA_CONTROL__HPP


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


#include "../../../Camera/include/ICamera.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ICameraControl
	{
	public:
		virtual ~ICameraControl();

		// Setters
		virtual void SetCamera(ICamera* camera) = 0;
	};
}


#endif // RENDERER__I_CAMERA_CONTROL__HPP