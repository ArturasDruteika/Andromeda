#ifndef API__RENDERER__I_CAMERA_CONTROL__HPP
#define API__RENDERER__I_CAMERA_CONTROL__HPP


#include "../Space/Camera/ICamera.hpp"


namespace Andromeda
{
	class ICameraControl
	{
	public:
		virtual ~ICameraControl() = default;

		// Setters
		virtual void SetCamera(ICamera* camera) = 0;
	};
}


#endif // API__RENDERER__I_CAMERA_CONTROL__HPP