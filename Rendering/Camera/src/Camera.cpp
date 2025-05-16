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

        Camera::Camera(const Camera& other)
        {
            m_pCameraImpl = new CameraImpl(*other.m_pCameraImpl);
        }

        Camera& Camera::operator=(const Camera& other)
        {
            if (this != &other)
            {
                delete m_pCameraImpl;
                m_pCameraImpl = new CameraImpl(*other.m_pCameraImpl);
            }
            return *this;
        }

        Camera::Camera(Camera&& other)
            : m_pCameraImpl(other.m_pCameraImpl)
        {
            other.m_pCameraImpl = nullptr;
        }

        Camera& Camera::operator=(Camera&& other)
        {
            if (this != &other)
            {
                delete m_pCameraImpl;
                m_pCameraImpl = other.m_pCameraImpl;
                other.m_pCameraImpl = nullptr;
            }
            return *this;
        }

        float Camera::GetYaw() const
        {
			return m_pCameraImpl->GetYaw();
        }

        float Camera::GetPitch() const
        {
			return m_pCameraImpl->GetPitch();
        }

        void Camera::SetYaw(float yaw)
        {
            m_pCameraImpl->SetYaw(yaw);
        }

        void Camera::SetPitch(float pitch)
        {
            m_pCameraImpl->SetPitch(pitch);
        }

        void Camera::SetRoll(float roll)
        {
            m_pCameraImpl->SetRoll(roll);
        }

        void Camera::SetRotation(float yaw, float pitch, float roll)
        {
            m_pCameraImpl->SetRotation(yaw, pitch, roll);
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

        void Camera::Move(const Math::Vec3& delta)
        {
			m_pCameraImpl->Move(delta);
        }

        void Camera::Rotate(float yaw, float pitch, float roll)
        {
			m_pCameraImpl->Rotate(yaw, pitch, roll);
        }
	}
}
