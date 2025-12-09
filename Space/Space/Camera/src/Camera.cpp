#include "../include/Camera.hpp"
#include "Math/Constants/include/Constants.hpp"


namespace Andromeda::Space
{
    Camera::Camera()
        : Camera(Math::Vec3(20.0f, 20.0f, 25.0f), -Math::PI_HALF, 0.0f)
    {
    }

    Camera::Camera(const Math::Vec3& position, float yawRadians, float pitchRadians)
		: PerspectiveControl(45.0f, 0.1f, 1000.0f, 1.0f)
        , CameraController(position)
    {
    }

    Camera::~Camera() = default;

    void Camera::Zoom(float deltaDistance)
    {
		CameraController::Zoom(deltaDistance);
        m_onDistanceChangeCallback(m_distance);
    }

    void Camera::SetOnDistanceChange(OnDistanceChange callback)
    {
        m_onDistanceChangeCallback = std::move(callback);
	}
}
