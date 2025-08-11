#ifndef RENDERING__INTERFACES__I_TRANSFORMABLE__HPP
#define RENDERING__INTERFACES__I_TRANSFORMABLE__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ITransformable
    {
    public:
        virtual ~ITransformable();

		// Getters
		virtual bool StateChanged() const = 0;
		virtual Math::Vec3 GetCenterPosition() const = 0;
        virtual Math::Mat4 GetModelMatrix() const = 0;
		// Setters
        virtual void SetModelMatrix(const Math::Mat4& modelMatrix) = 0;

		virtual void ResetState() = 0;
        virtual void Translate(const Math::Vec3& translation) = 0;
        virtual void TranslateDelta(const Math::Vec3& translationDelta) = 0;
        virtual void Rotate(const Math::Vec3& rotation) = 0;
        virtual void RotateX(float angle) = 0;
        virtual void RotateY(float angle) = 0;
        virtual void RotateZ(float angle) = 0;
        virtual void Scale(const Math::Vec3& scale) = 0;
    };
}


#endif // RENDERING__INTERFACES__I_TRANSFORMABLE__HPP