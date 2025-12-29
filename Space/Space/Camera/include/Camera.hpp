#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP


#include "PerspectiveControl.hpp"
#include "CameraController.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Camera/ICamera.hpp"
#include "Math/Constants/include/Constants.hpp"


namespace Andromeda::Space
{
    class SPACE_API Camera
        : public virtual ICamera
        , public PerspectiveControl
        , public CameraController
    {
    public:
        Camera();
        Camera(const Math::Vec3& position, float yawRadians = -Math::PI_HALF, float pitchRadians = 0.0f);
        ~Camera();

        void Zoom(float deltaDistance);
        void SetOnDistanceChange(OnDistanceChange callback);

    private:
        OnDistanceChange m_onDistanceChangeCallback;
    };
}


#endif // RENDERING__CAMERA__HPP