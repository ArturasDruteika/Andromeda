#ifndef API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP

#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
    class IScalable
    {
    public:
        virtual ~IScalable() = default;

        // Getters
        virtual bool StateChanged() const = 0;
        virtual const Math::Vec3& GetScale() const = 0;
		virtual const Math::Mat4& GetScaleMatrix() const = 0;
        // Setters
        virtual void ResetState() = 0;
        virtual void SetScale(const Math::Vec3& scale) = 0;

        virtual void Scale(const Math::Vec3& scale) = 0;
        virtual void Scale(float uniformScale) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP