#ifndef SPACE__TRANSFORMATIONS__ROTATABLE__HPP
#define SPACE__TRANSFORMATIONS__ROTATABLE__HPP

#include "Andromeda/Space/Transformations/IRotatable.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Math/LinearAlgebra/include/Quaternions.hpp"


namespace Andromeda
{
    class Rotatable
        : public virtual IRotatable
    {
    public:
        Rotatable();
        ~Rotatable() override;

        // Getters
        bool StateChanged() const override;
        const Math::Vec3& GetRotation() const override; // Euler radians (derived)
        const Math::Mat4& GetRotationMatrix() const override;
        const Math::Quaternion& GetOrientation() const override;

        // Setters
        void ResetState() override;
        void SetRotation(const Math::Vec3& rotation) override;
        void Rotate(const Math::Vec3& rotation) override;
        void Rotate(const Math::Quaternion& delta) override;
        void RotateX(float angle) override;
        void RotateY(float angle) override;
        void RotateZ(float angle) override;

    protected:
        void UpdateRotationDerivedData();

    private:
        bool m_stateChanged;
        Math::Vec3 m_rotation;
        Math::Mat4 m_rotationMatrix;
        Math::Quaternion m_orientation;
    };
}

#endif // SPACE__TRANSFORMATIONS__ROTATABLE__HPP
