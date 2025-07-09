#ifndef RENDERING__MATERIALS__HPP
#define RENDERING__MATERIALS__HPP


#include "pch.hpp"
#include "MaterialTypes.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
        class Material
        {
        public:
            Material();
            ~Material();

            // Getters
            float GetShininess() const;
            std::string GetName() const;
            Math::Vec3 GetAmbient() const;
            Math::Vec3 GetDiffuse() const;
            Math::Vec3 GetSpecular() const;
            // Setters
            void SetShininess(float shininess);
            void SetName(const std::string& name);
            void SetAmbient(const Math::Vec3& ambient);
            void SetDiffuse(const Math::Vec3& diffuse);
            void SetSpecular(const Math::Vec3& specular);

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
}


#endif // RENDERING__MATERIALS__HPP