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

        Camera::Camera(Camera&& other) noexcept
            : m_pCameraImpl(other.m_pCameraImpl)
        {
            other.m_pCameraImpl = nullptr;
        }

        Camera& Camera::operator=(Camera&& other) noexcept
        {
            if (this != &other)
            {
                delete m_pCameraImpl;
                m_pCameraImpl = other.m_pCameraImpl;
                other.m_pCameraImpl = nullptr;
            }
            return *this;
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

        void Camera::Rotate(float yaw, float pitch, float roll)
        {
			m_pCameraImpl->Rotate(yaw, pitch, roll);
        }
	}
}
