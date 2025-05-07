#include "../include/Camera.hpp"
#include "../include/CameraImpl.hpp"


namespace Andromeda
{
    namespace Rendering
    {
        Camera::Camera()
            : m_pCameraImpl{ new Camera::CameraImpl() }
        {
        }

        Camera::Camera(const Math::Vec3& position, float yawRadians, float pitchRadians)
			: m_pCameraImpl{ new Camera::CameraImpl(position, yawRadians, pitchRadians) }
        {
        }

        Camera::~Camera()
        {
			delete m_pCameraImpl;
        }

        float Camera::GetYaw() const
        {
			return m_pCameraImpl->GetYaw();
        }

        float Camera::GetPitch() const
        {
			return m_pCameraImpl->GetPitch();
        }

        float Camera::GetRoll() const
        {
			return m_pCameraImpl->GetRoll();
        }

        Math::Mat4 Camera::GetViewMatrix() const
        {
			return m_pCameraImpl->GetViewMatrix();
        }

        Math::Vec3 Camera::GetPosition() const
        {
			return m_pCameraImpl->GetPosition();
        }

        Math::Vec3 Camera::GetForward() const
        {
            return m_pCameraImpl->GetForward();
        }

        Math::Vec3 Camera::GetRight() const
        {
			return m_pCameraImpl->GetRight();
        }

        Math::Vec3 Camera::GetUp() const
        {
			return m_pCameraImpl->GetUp();
        }

        void Camera::SetPosition(const Math::Vec3& position)
        {
			m_pCameraImpl->SetPosition(position);
        }

        void Camera::SetRotation(float yawRadians, float pitchRadians)
        {
			m_pCameraImpl->SetRotation(yawRadians, pitchRadians);
        }

        void Camera::Move(const Math::Vec3& delta)
        {
			m_pCameraImpl->Move(delta);
        }

        void Camera::Rotate(float deltaYawRad, float deltaPitchRad)
        {
			m_pCameraImpl->Rotate(deltaYawRad, deltaPitchRad);
        }
	}
}
