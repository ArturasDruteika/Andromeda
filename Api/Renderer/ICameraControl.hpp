#ifndef API__RENDERER__I_CAMERA_CONTROL__HPP
#define API__RENDERER__I_CAMERA_CONTROL__HPP


#include "../Camera/ICamera.hpp"


namespace Andromeda
{
	class ICameraControl
	{
	public:
		virtual ~ICameraControl();

		// Setters
		virtual void SetCamera(ICamera* camera) = 0;
	};
}


#endif // API__RENDERER__I_CAMERA_CONTROL__HPP