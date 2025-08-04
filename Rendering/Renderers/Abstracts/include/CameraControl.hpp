#ifndef RENDERER__CAMERA_CONTROL__HPP
#define RENDERER__CAMERA_CONTROL__HPP


#include "../../../Camera/include/ICamera.hpp"


namespace Andromeda::Rendering
{
	class CameraControl
	{
	public:
		CameraControl();
		~CameraControl();

		// Setters
		void SetCamera(ICamera* camera);

	protected:
		ICamera* m_pCamera;
	};
}


#endif // RENDERER__CAMERA_CONTROL__HPP