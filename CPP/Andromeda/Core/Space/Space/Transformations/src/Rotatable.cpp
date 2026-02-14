#include "../include/Rotatable.hpp"
#include "Math/LinearAlgebra/include/Quaternions.hpp"


namespace Andromeda
{
    Rotatable::Rotatable()
        : m_stateChanged{ false }
        , m_rotation{ 0.0f }
        , m_rotationMatrix{}
        , m_orientation(Math::Quaternion::Identity())
    {
        UpdateRotationDerivedData();
    }

    Rotatable::~Rotatable() = default;

    bool Rotatable::StateChanged() const
    {
        return m_stateChanged;
    }

    const Math::Vec3& Rotatable::GetRotation() const
    {
        return m_rotation;
    }

    const Math::Mat4& Rotatable::GetRotationMatrix() const
    {
        return m_rotationMatrix;
    }

    const Math::Quaternion& Rotatable::GetOrientation() const
    {
        return m_orientation;
    }

    void Rotatable::ResetState()
    {
        m_stateChanged = false;
    }

    void Rotatable::SetRotation(const Math::Vec3& rotation)
    {
        // rotation is Euler XYZ in radians
        m_orientation = Math::QuaternionOps::FromEulerXYZ(rotation[0], rotation[1], rotation[2]);
        m_orientation = Math::QuaternionOps::Normalize(m_orientation);

        UpdateRotationDerivedData();
        m_stateChanged = true;
    }

    void Rotatable::Rotate(const Math::Vec3& rotation)
    {
        // rotation is Euler delta XYZ in radians
        const Math::Quaternion delta = Math::QuaternionOps::FromEulerXYZ(rotation[0], rotation[1], rotation[2]);

        Rotate(delta);
    }

    void Rotatable::Rotate(const Math::Quaternion& delta)
    {
        // Apply delta in local space: new = delta * current
        m_orientation = Math::QuaternionOps::Multiply(delta, m_orientation);
        m_orientation = Math::QuaternionOps::Normalize(m_orientation);

        UpdateRotationDerivedData();
        m_stateChanged = true;
    }

    void Rotatable::RotateX(float angle)
    {
        Rotate(Math::QuaternionOps::AngleAxis(angle, Math::Vec3(1.0f, 0.0f, 0.0f)));
    }

    void Rotatable::RotateY(float angle)
    {
        Rotate(Math::QuaternionOps::AngleAxis(angle, Math::Vec3(0.0f, 1.0f, 0.0f)));
    }

    void Rotatable::RotateZ(float angle)
    {
        Rotate(Math::QuaternionOps::AngleAxis(angle, Math::Vec3(0.0f, 0.0f, 1.0f)));
    }

    void Rotatable::UpdateRotationDerivedData()
    {
        // Euler is derived for UI/debug only
        m_rotation = Math::QuaternionOps::ToEulerXYZ(m_orientation);

        // Rotation matrix derived from quaternion
        m_rotationMatrix = Math::QuaternionOps::ToMat4(m_orientation);
    }
}
