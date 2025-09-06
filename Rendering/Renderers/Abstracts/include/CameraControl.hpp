#ifndef RENDERER__CAMERA_CONTROL__HPP
#define RENDERER__CAMERA_CONTROL__HPP


#include "../../../Camera/Interfaces/include/ICamera.hpp"


namespace Andromeda::Rendering
{
	class CameraControl
	{
	public:
		CameraControl();
		~CameraControl();

		// Setters
		void SetCamera(ICamera* camera);
		void SetCameraAspect(int width, int height);
		// TODO: add more camera controls as needed

	protected:
		ICamera* m_pCamera;
	};
}


#endif // RENDERER__CAMERA_CONTROL__HPP