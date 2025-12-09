#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP

#define GLM_ENABLE_EXPERIMENTAL

#include "Camera.hpp"
#include "PerspectiveControl.hpp"
#include "CameraController.hpp"
#include "Andromeda/Space/Camera/ICamera.hpp"


namespace Andromeda::Space
{
    class Camera
        : public PerspectiveControl
        , public CameraController
        , public ICamera
    {
    public:
        Camera();
        Camera(const Math::Vec3& position, float yawRadians, float pitchRadians);
        ~Camera();

        void Zoom(float deltaDistance);
        void SetOnDistanceChange(OnDistanceChange callback);

    private:
        OnDistanceChange m_onDistanceChangeCallback;
    };
}


#endif // RENDERING__CAMERA__HPP