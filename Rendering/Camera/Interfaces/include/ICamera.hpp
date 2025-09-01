#ifndef RENDERING__I_CAMERA__HPP
#define RENDERING__I_CAMERA__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    using OnDistanceChange = std::function<void(float)>;

    class RENDERING_API ICamera
    {
    public:
        virtual ~ICamera();

        // Getters
        virtual Math::Mat4 GetViewMatrix() const = 0;
        virtual Math::Vec3 GetPosition() const = 0;
        virtual Math::Vec3 GetForward() const = 0;
        virtual Math::Vec3 GetRight() const = 0;
        virtual Math::Vec3 GetUp() const = 0;

        virtual void Rotate(float yaw, float pitch, float roll) = 0;
        virtual void Zoom(float deltaDistance) = 0;
        virtual void SetOnDistanceChange(OnDistanceChange callback) = 0;
    };
}


#endif // RENDERING__I_CAMERA__HPP