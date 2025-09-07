#ifndef RENDERING__I_CAMERA_CONTROLLER__HPP
#define RENDERING__I_CAMERA_CONTROLLER__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
    using OnDistanceChange = std::function<void(float)>;

    // Mutation & events for controlling the camera.
    class RENDERING_API ICameraController
    {
    public:
        virtual ~ICameraController();

        virtual void Rotate(float yaw, float pitch, float roll) = 0;
        virtual void Zoom(float deltaDistance) = 0;

        // Observer for distance (zoom) changes.
        virtual void SetOnDistanceChange(OnDistanceChange callback) = 0;
    };
}


#endif // RENDERING__I_CAMERA_CONTROLLER__HPP
