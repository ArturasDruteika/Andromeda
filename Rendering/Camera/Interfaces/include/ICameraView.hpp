#ifndef RENDERING__I_CAMERA_VIEW__HPP
#define RENDERING__I_CAMERA_VIEW__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "IPerspectiveControl.hpp"
#include "pch.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    // Read-only access to camera orientation and position.
    class RENDERING_API ICameraView
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


#endif // RENDERING__I_CAMERA_VIEW__HPP
