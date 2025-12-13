#ifndef API__SPACE__TRANSFORMATIONS__I_TRANSFORMABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_TRANSFORMABLE__HPP


#include "IRotatable.hpp"
#include "IScalable.hpp"
#include "ITranslatable.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
    class ITransformable
    : public virtual IRotatable
    , public virtual IScalable
    , public virtual ITranslatable
    {
    public:
        virtual ~ITransformable() = default;

        // Getters
		virtual bool StateChanged() const = 0;
        virtual Math::Mat4 GetModelMatrix() const = 0;

		// Getters
		virtual Math::Vec3 GetCenterPosition() const = 0;
        virtual Math::Mat4 GetModelMatrix() const = 0;
		// Setters
        virtual void SetModelMatrix(const Math::Mat4& modelMatrix) = 0;

		virtual void ResetState() = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_TRANSFORMABLE__HPP