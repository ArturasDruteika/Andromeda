#include "../include/Camera.hpp"


constexpr Andromeda::Math::Vec3 DEFAULT_CAMERA_POSITION = { 10.0f, 10.0f , 10.0f };


namespace Andromeda::Space
{
    Camera::Camera()
        : Camera(DEFAULT_CAMERA_POSITION, -Math::PI_HALF, 0.0f)
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
