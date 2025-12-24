#ifndef SPACE__SCENE__CAMERA_HANDLER__HPP
#define SPACE__SCENE__CAMERA_HANDLER__HPP


#include "../../Camera/include/Camera.hpp"
#include "Andromeda/Space/Scene/ICameraHandler.hpp"


namespace Andromeda::Space
{
	class CameraHandler
		: public ICameraHandler
	{
	public:
		CameraHandler();
		~CameraHandler() override;

		ICamera* GetActiveCamera() override;
		void SetActiveCamera(ICamera* camera) override;

	protected:
		Camera* m_camera;
	};
}


#endif // API_CAMERA_HANDLER__I_CAMERA_HANDLER__HPP