#include "../include/CameraControl.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
	CameraControl::CameraControl()
		: m_pCamera{ nullptr }
	{
	}

    CameraControl::~CameraControl() = default;

	void CameraControl::SetCamera(ICamera* camera)
	{
		if (camera == nullptr)
		{
			spdlog::error("Camera is nullptr.");
			return;
		}
		m_pCamera = camera;
	}

	void CameraControl::SetCameraAspect(int width, int height)
	{
		if (m_pCamera == nullptr)
			return;
		float aspect = static_cast<float>(width) / static_cast<float>(height);
		m_pCamera->SetAspect(aspect);
	}
}
