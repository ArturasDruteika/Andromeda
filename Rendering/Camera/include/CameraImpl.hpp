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

            // Getters
            float GetDistance() const;
            Math::Mat4 GetViewMatrix() const;
            Math::Vec3 GetPosition() const;
            Math::Vec3 GetForward() const;
            Math::Vec3 GetRight() const;
            Math::Vec3 GetUp() const;
            Math::Vec3 GetTarget() const;

            void Rotate(float deltaYawRad = 0.0f, float deltaPitchRad = 0.0f, float roll = 0.0f);

        private:
            void UpdateDirection();
            void CalculateViewMatrix();

            float m_distance;

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