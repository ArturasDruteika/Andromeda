#ifndef API__CAMERA_HANDLER__I_CAMERA_HANDLER__HPP
#define API__CAMERA_HANDLER__I_CAMERA_HANDLER__HPP


#include "../Camera/ICamera.hpp"


namespace Andromeda
{
	class ICameraHandler
	{
	public:
		virtual ~ICameraHandler() = default;

		virtual ICamera* GetActiveCamera() = 0;
		virtual void SetActiveCamera(ICamera* camera) = 0;
	};
}


#endif // API_CAMERA_HANDLER__I_CAMERA_HANDLER__HPP