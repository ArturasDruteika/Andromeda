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
}
