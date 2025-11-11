#ifndef API__I_CAMERA_CONTROLLER__HPP
#define API__I_CAMERA_CONTROLLER__HPP


#include "pch.hpp"


namespace Andromeda
{
    using OnDistanceChange = std::function<void(float)>;

    // Mutation & events for controlling the camera.
    class ICameraController
    {
    public:
        virtual ~ICameraController();

        virtual void Rotate(float yaw, float pitch, float roll) = 0;
        virtual void Zoom(float deltaDistance) = 0;

        // Observer for distance (zoom) changes.
        virtual void SetOnDistanceChange(OnDistanceChange callback) = 0;
    };
}


#endif // API__I_CAMERA_CONTROLLER__HPP
