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

        float Camera::GetFieldOfViewDegrees() const
        {
            return m_pCameraImpl->GetFieldOfViewDegrees();
        }

        float Camera::GetNearPlane() const
        {
            return m_pCameraImpl->GetNearPlane();
        }

        float Camera::GetFarPlane() const
        {
            return m_pCameraImpl->GetFarPlane();
        }

        float Camera::GetAspect() const
        {
            return m_pCameraImpl->GetAspect();
        }

        const Math::Mat4& Camera::GetProjection() const
        {
            return m_pCameraImpl->GetProjection();
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

        void Camera::SetFieldOfViewDegrees(float fovDeg)
        {
            m_pCameraImpl->SetFieldOfViewDegrees(fovDeg);
        }

        void Camera::SetNearPlane(float nearPlane)
        {
            m_pCameraImpl->SetNearPlane(nearPlane);
        }

        void Camera::SetFarPlane(float farPlane)
        {
            m_pCameraImpl->SetFarPlane(farPlane);
        }

        void Camera::SetAspect(float aspect)
        {
            m_pCameraImpl->SetAspect(aspect);
        }

        void Camera::Rotate(float yaw, float pitch, float roll)
        {
			m_pCameraImpl->Rotate(yaw, pitch, roll);
        }

        void Camera::Zoom(float deltaDistance)
        {
            m_pCameraImpl->Zoom(deltaDistance);
        }

        void Camera::SetOnDistanceChange(OnDistanceChange callback)
        {
			m_pCameraImpl->SetOnDistanceChange(callback);
        }
	}
}
