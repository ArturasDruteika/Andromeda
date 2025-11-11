#ifndef API__I_CAMERA_CONTROL__HPP
#define API__I_CAMERA_CONTROL__HPP


#include "ICamera.hpp"


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


#endif // API__I_CAMERA_CONTROL__HPP