#ifndef API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
    class ITranslatable
    {
    public:
        virtual ~ITranslatable() = default;

        // Getters
        virtual Math::Vec3 GetPosition() const = 0;
        // Setters
        virtual void SetPosition(const Math::Vec3& position) = 0;
        
        virtual void Translate(const Math::Vec3& translation) = 0;
        virtual void TranslateDelta(const Math::Vec3& translationDelta) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP