#ifndef API__I_CAMERA_VIEW__HPP
#define API__I_CAMERA_VIEW__HPP


#include "IPerspectiveControl.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
    // Read-only access to camera orientation and position.
    class ICameraView
        : public IPerspectiveControl
    {
    public:
        virtual ~ICameraView();

        // Getters
        virtual Math::Mat4 GetViewMatrix() const = 0;
        virtual Math::Vec3 GetPosition() const = 0;
        virtual Math::Vec3 GetForward() const = 0;
        virtual Math::Vec3 GetRight() const = 0;
        virtual Math::Vec3 GetUp() const = 0;
    };
}


#endif // API__I_CAMERA_VIEW__HPP
