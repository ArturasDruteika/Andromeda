#ifndef API__SPACE__TRANSFORMATIONS__I_ROTATABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_ROTATABLE__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Math/LinearAlgebra/include/Quaternions.hpp"


namespace Andromeda
{
    class IRotatable
    {
    public:
        virtual ~IRotatable() = default;

        // Getters
        virtual bool StateChanged() const = 0;
        virtual const Math::Vec3& GetRotation() const = 0;
        virtual const Math::Mat4& GetRotationMatrix() const = 0;
        virtual const Math::Quaternion& GetOrientation() const = 0;

        // Setters
        virtual void ResetState() = 0;
        virtual void SetRotation(const Math::Vec3& rotation) = 0;
        virtual void Rotate(const Math::Vec3& rotation) = 0;
        virtual void Rotate(const Math::Quaternion& delta) = 0;
        virtual void RotateX(float angle) = 0;
        virtual void RotateY(float angle) = 0;
        virtual void RotateZ(float angle) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_ROTATABLE__HPP
