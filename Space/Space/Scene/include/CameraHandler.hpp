#ifndef SPACE__SCENE__CAMERA_HANDLER__HPP
#define SPACE__SCENE__CAMERA_HANDLER__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ICameraHandler.hpp"


namespace Andromeda::Space
{
	// Forward declaration
	class Camera;


	class SPACE_API CameraHandler
		: public virtual ICameraHandler
	{
	public:
		CameraHandler();
		~CameraHandler() override;

		ICamera* GetActiveCamera() const override;
		void SetActiveCamera(ICamera* camera) override;

	protected:
		Camera* m_pCamera;
	};
}


#endif // API_CAMERA_HANDLER__I_CAMERA_HANDLER__HPP