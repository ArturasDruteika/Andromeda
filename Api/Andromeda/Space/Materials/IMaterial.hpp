#ifndef ANDROMEDA__MATERIALS__I_MATERIAL__HPP
#define ANDROMEDA__MATERIALS__I_MATERIAL__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include <string>


namespace Andromeda
{
    class IMaterial
    {
    public:
        virtual ~IMaterial() = default;

        // Getters
        virtual float GetShininess() const = 0;
        virtual const std::string& GetName() const = 0;
        virtual const Math::Vec3& GetAmbient() const = 0;
        virtual const Math::Vec3& GetDiffuse() const = 0;
        virtual const Math::Vec3& GetSpecular() const = 0;
        // Setters
        virtual void SetShininess(float shininess) = 0;
        virtual void SetName(const std::string& name) = 0;
        virtual void SetAmbient(const Math::Vec3& ambient) = 0;
        virtual void SetDiffuse(const Math::Vec3& diffuse) = 0;
        virtual void SetSpecular(const Math::Vec3& specular) = 0;
    };
}


#endif // ANDROMEDA__MATERIALS__I_MATERIAL__HPP