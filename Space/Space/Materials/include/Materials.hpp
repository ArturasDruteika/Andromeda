#ifndef SPACE__MATERIALS__HPP
#define SPACE__MATERIALS__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Andromeda/Space/Materials/IMaterial.hpp"


namespace Andromeda::Space
{
    class SPACE_API Material
		: public virtual IMaterial
    {
    public:
        Material();
        ~Material();

        // Getters
        float GetShininess() const override;
        const std::string& GetName() const override;
        const Math::Vec3& GetAmbient() const override;
        const Math::Vec3& GetDiffuse() const override;
        const Math::Vec3& GetSpecular() const override;
        // Setters
        void SetShininess(float shininess) override;
        void SetName(const std::string& name) override;
        void SetAmbient(const Math::Vec3& ambient) override;
        void SetDiffuse(const Math::Vec3& diffuse) override;
        void SetSpecular(const Math::Vec3& specular) override;

    private:
        bool ValidateVec3Components(const Math::Vec3& vector);

    private:
        float m_shininess;
        std::string m_name;
        Math::Vec3 m_ambient;
        Math::Vec3 m_diffuse;
        Math::Vec3 m_specular;
    };
}


#endif // SPACE__MATERIALS__HPP