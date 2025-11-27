#ifndef RENDERING__CAMERA_IMPL__HPP
#define RENDERING__CAMERA_IMPL__HPP

#define GLM_ENABLE_EXPERIMENTAL

#include "Camera.hpp"
#include "../../Abstracts/include/PerspectiveControl.hpp"
#include "../../Abstracts/include/CameraController.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"


namespace Andromeda
{
    namespace Rendering
    {
        class Camera::CameraImpl
            : public PerspectiveControl
            , public CameraController
        {
        public:
            CameraImpl();
            CameraImpl(const Math::Vec3& position, float yawRadians, float pitchRadians);
            ~CameraImpl();

            void Zoom(float deltaDistance);
            void SetOnDistanceChange(OnDistanceChange callback);

        private:
            OnDistanceChange m_onDistanceChangeCallback;
        };
    }
}

#endif // RENDERING__CAMERA_IMPL__HPP