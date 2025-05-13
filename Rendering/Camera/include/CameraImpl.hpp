#ifndef RENDERING__CAMERA_IMPL__HPP
#define RENDERING__CAMERA_IMPL__HPP

#define GLM_ENABLE_EXPERIMENTAL

#include "Camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Andromeda
{
    namespace Rendering
    {
        class Camera::CameraImpl
        {
        public:
            CameraImpl();
            CameraImpl(const Math::Vec3& position, float yawRadians, float pitchRadians);
            ~CameraImpl();

            float GetDistance() const;
            float GetYaw() const;
            float GetPitch() const;
            void SetRotation(float yawRadians, float pitchRadians);
            Math::Mat4 GetViewMatrix() const;
            Math::Vec3 GetPosition() const;
            Math::Vec3 GetForward() const;
            Math::Vec3 GetRight() const;
            Math::Vec3 GetUp() const;
            Math::Vec3 GetTarget() const;

            void SetPosition(const Math::Vec3& position);
            void SetOrientation(const glm::quat& orientation);

            void Move(const Math::Vec3& delta);
            void Rotate(float deltaYawRad, float deltaPitchRad);

            bool IsUpsideDown() const;

        private:
            void UpdateDirection();
            void CalculateViewMatrix();

            float m_distance;
            float m_yaw;
            float m_pitch;

            glm::vec3 m_xAxis;
            glm::vec3 m_yAxis;
            glm::vec3 m_zAxis;
            glm::vec3 m_position;
            glm::vec3 m_forward;
            glm::vec3 m_right;
            glm::vec3 m_up;
            glm::vec3 m_worldUp;
            glm::vec3 m_targetCoords;
            glm::mat4 m_viewMatrix;
            glm::quat m_orientation;
        };
    }
}

#endif // RENDERING__CAMERA_IMPL__HPP