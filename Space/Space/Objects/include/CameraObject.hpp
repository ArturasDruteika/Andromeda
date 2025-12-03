#ifndef RENDERING__ABSTRACTS__TRANSFORMABLE__HPP
#define RENDERING__ABSTRACTS__TRANSFORMABLE__HPP


#include "Space/Transformations/include/TransformationTypes.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Andromeda::Space
{
    class Transformable
    {
    public:
        Transformable(const Math::Vec3& centerPosition);
        ~Transformable();

		// Getters
        bool StateChanged() const;
		Math::Vec3 GetCenterPosition() const;
        Math::Mat4 GetModelMatrix() const;
		// Setters
        void SetModelMatrix(const Math::Mat4& modelMatrix);

        void ResetState();
        void Translate(const Math::Vec3& translation);
        void TranslateDelta(const Math::Vec3& translationDelta);
        void Rotate(const Math::Vec3& rotation);
        void RotateX(float angle);
        void RotateY(float angle);
        void RotateZ(float angle);
        void Scale(const Math::Vec3& scale);
        void UpdateModelMatrix(const Space::TransformationType& transformationType);

    private:
        // Transformation matrices
        glm::mat4 ConstructTranslationMatrix() const;
        glm::mat4 ConstructRotationMatrix() const;
        glm::mat4 ConstructScaleMatrix() const;

    protected:
        bool m_stateChanged;
        // Transform components
        glm::vec3 m_centerPosition;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
        glm::mat4 m_translationMatrix;
        glm::mat4 m_rotationMatrix;
        glm::mat4 m_scaleMatrix;
        glm::mat4 m_modelMatrix;
    };
}


#endif // RENDERING__ABSTRACTS__TRANSFORMABLE__HPP