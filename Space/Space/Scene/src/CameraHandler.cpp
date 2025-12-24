#include "../include/CameraHandler.hpp"


namespace Andromeda::Space
{
	Space::CameraHandler::CameraHandler()
		: m_camera{ nullptr }
	{
	}

	Space::CameraHandler::~CameraHandler()
	{
		delete m_camera;
	}

	ICamera* Space::CameraHandler::GetActiveCamera()
	{
		return m_camera;
	}

	void Space::CameraHandler::SetActiveCamera(ICamera* camera)
	{
		if (camera == nullptr || m_camera != camera)
		{
			delete m_camera;
			m_camera = nullptr;
			return;
		}
		m_camera = dynamic_cast<Camera*>(camera);
	}
}