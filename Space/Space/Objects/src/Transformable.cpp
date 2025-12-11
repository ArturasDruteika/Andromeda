#include "../include/Transformable.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraOperations.hpp"


namespace Andromeda::Space
{
    Transformable::Transformable(const Math::Vec3& centerPosition)
        : m_stateChanged(true),
        m_centerPosition(centerPosition),
        m_rotation(0.0f, 0.0f, 0.0f),
        m_scale(1.0f, 1.0f, 1.0f),
        m_translationMatrix(1.0f),
        m_rotationMatrix(1.0f),
        m_scaleMatrix(1.0f),
        m_modelMatrix(1.0f)
    {
        m_translationMatrix = ConstructTranslationMatrix();
        m_rotationMatrix = ConstructRotationMatrix();
        m_scaleMatrix = ConstructScaleMatrix();

        m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
    }

    Transformable::~Transformable() = default;

    // Getters

    bool Transformable::StateChanged() const
    {
        return m_stateChanged;
    }

    Math::Vec3 Transformable::GetCenterPosition() const
    {
        return m_centerPosition;
    }

    Math::Mat4 Transformable::GetModelMatrix() const
    {
        return m_modelMatrix;
    }

    // Setters

    void Transformable::SetModelMatrix(const Math::Mat4& modelMatrix)
    {
        m_modelMatrix = modelMatrix;
        m_stateChanged = true;
    }

    void Transformable::ResetState()
    {
        m_stateChanged = false;
    }

    void Transformable::Translate(const Math::Vec3& translation)
    {
        m_centerPosition = translation;
        UpdateModelMatrix(Space::TransformationType::Translation);
    }

    void Transformable::TranslateDelta(const Math::Vec3& translationDelta)
    {
        m_centerPosition += translationDelta;
        UpdateModelMatrix(Space::TransformationType::Translation);
    }

    void Transformable::Rotate(const Math::Vec3& rotation)
    {
        m_rotation = rotation;
        UpdateModelMatrix(Space::TransformationType::Rotation);
    }

    void Transformable::RotateX(float angle)
    {
        m_rotation[0] += angle;
        UpdateModelMatrix(Space::TransformationType::Rotation);
    }

    void Transformable::RotateY(float angle)
    {
        m_rotation[1] += angle;
        UpdateModelMatrix(Space::TransformationType::Rotation);
    }

    void Transformable::RotateZ(float angle)
    {
        m_rotation[2] += angle;
        UpdateModelMatrix(Space::TransformationType::Rotation);
    }

    void Transformable::Scale(const Math::Vec3& scale)
    {
        m_scale = scale;
        UpdateModelMatrix(Space::TransformationType::Scale);
    }

    void Transformable::UpdateModelMatrix(const Space::TransformationType& transformationType)
    {
        switch (transformationType)
        {
        case Space::TransformationType::Translation:
            m_translationMatrix = ConstructTranslationMatrix();
            break;

        case Space::TransformationType::Rotation:
            m_rotationMatrix = ConstructRotationMatrix();
            break;

        case Space::TransformationType::Scale:
            m_scaleMatrix = ConstructScaleMatrix();
            break;

        case Space::TransformationType::All:
        default:
            m_translationMatrix = ConstructTranslationMatrix();
            m_rotationMatrix = ConstructRotationMatrix();
            m_scaleMatrix = ConstructScaleMatrix();
            break;
        }

        m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
        m_stateChanged = true;
    }

    // Private helpers

    Math::Mat4 Transformable::ConstructTranslationMatrix() const
    {
        Math::Mat4 translation(1.0f);
        translation = Math::LinAlgOps::Translate(translation, m_centerPosition);
        return translation;
    }

    Math::Mat4 Transformable::ConstructRotationMatrix() const
    {
        Math::Mat4 rotation(1.0f);

        // X, then Y, then Z rotation (you can change order if needed)
        rotation = Math::LinAlgOps::Rotate(rotation, m_rotation[0], Math::Vec3(1.0f, 0.0f, 0.0f));
        rotation = Math::LinAlgOps::Rotate(rotation, m_rotation[1], Math::Vec3(0.0f, 1.0f, 0.0f));
        rotation = Math::LinAlgOps::Rotate(rotation, m_rotation[2], Math::Vec3(0.0f, 0.0f, 1.0f));

        return rotation;
    }

    Math::Mat4 Transformable::ConstructScaleMatrix() const
    {
        Math::Mat4 scale(1.0f);
        scale = Math::LinAlgOps::Scale(scale, m_scale);
        return scale;
    }

}
