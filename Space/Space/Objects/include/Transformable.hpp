#ifndef RENDERING__ABSTRACTS__TRANSFORMABLE__HPP
#define RENDERING__ABSTRACTS__TRANSFORMABLE__HPP


#include "../../Transformations/include/TransformationTypes.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Andromeda/Space/Objects/ITransformable.hpp"


namespace Andromeda::Space
{
    class Transformable
        : public virtual ITransformable
    {
    public:
        Transformable(const Math::Vec3& centerPosition);
        ~Transformable();

        // Getters
        bool StateChanged() const override;
        Math::Vec3 GetCenterPosition() const override;
        Math::Mat4 GetModelMatrix() const override;
        // Setters
        void SetModelMatrix(const Math::Mat4& modelMatrix) override;

        void ResetState() override;
        void Translate(const Math::Vec3& translation) override;
        void TranslateDelta(const Math::Vec3& translationDelta) override;
        void Rotate(const Math::Vec3& rotation) override;
        void RotateX(float angle) override;
        void RotateY(float angle) override;
        void RotateZ(float angle) override;
        void Scale(const Math::Vec3& scale) override;
        void UpdateModelMatrix(const Space::TransformationType& transformationType);

    private:
        // Transformation matrices
        Math::Mat4 ConstructTranslationMatrix() const;
        Math::Mat4 ConstructRotationMatrix() const;
        Math::Mat4 ConstructScaleMatrix() const;

    protected:
        bool m_stateChanged;
        // Transform components
        Math::Vec3 m_centerPosition;
        Math::Vec3 m_rotation;
        Math::Vec3 m_scale;
        Math::Mat4 m_translationMatrix;
        Math::Mat4 m_rotationMatrix;
        Math::Mat4 m_scaleMatrix;
        Math::Mat4 m_modelMatrix;
    };
}


#endif // RENDERING__ABSTRACTS__TRANSFORMABLE__HPP