#ifndef SPACE__LIGHT_DATA__HPP
#define SPACE__LIGHT_DATA__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Light/LightTypes.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
    class SPACE_API LightData
    {
    public:
        LightData(
            float intensity = 1.0f,
            float range = 100.0f,
            float innerCutoff = 12.5f,
            float outerCutoff = 17.5f,
            float attenuationConstant = 1.0f,
            float attenuationLinear =  0.05f ,
            float attenuationQuadratic = 0.001f,
            const Math::Vec3& diffuseIntensity = Math::Vec3{ 1.0f, 1.0f, 1.0f },
            const Math::Vec3& specularIntensity = Math::Vec3{ 1.0f, 1.0f, 1.0f },
            const Math::Vec3& position = Math::Vec3{ 0.0f, 0.0f, 0.0f },
            const Math::Vec3& color = Math::Vec3{ 1.0f, 1.0f, 1.0f },
            const Math::Vec3& direction = Math::Vec3{ 0.0f, -1.0f, 0.0f },
            const LightType& lightType = LightType::None
        );
        ~LightData();

        // Getters
        float GetIntensity() const;
        float GetRange() const;
        float GetInnerCutoff() const;
        float GetOuterCutoff() const;
        float GetAttenuationConstant() const;
        float GetAttenuationLinear() const;
        float GetAttenuationQuadratic() const;
        Math::Vec3 GetDiffuseIntensity() const;
        Math::Vec3 GetSpecularIntensity() const;
        LightType GetLightType() const;
        Math::Vec3 GetPosition() const;
        Math::Vec3 GetColor() const;
        Math::Vec3 GetDirection() const;
        // Setters
        void SetIntensity(float intensity);
        void SetRange(float range);
        void SetInnerCutoff(float innerCutoff);
        void SetOuterCutoff(float outerCutoff);
        void SetAttenuationConstant(float constant);
        void SetAttenuationLinear(float linear);
        void SetAttenuationQuadratic(float quadratic);
        void SetDiffuseIntensity(const Math::Vec3& diffuseIntensity);
        void SetSpecularIntensity(const Math::Vec3& specularIntensity);
        void SetLightType(const LightType& lightType);
        void SetPosition(const Math::Vec3& position);
        void SetColor(const Math::Vec3& color);
        void SetDirection(const Math::Vec3& direction);

    private:
        float m_intensity;
        float m_range;
        // TODO: Move these to the child classes once the spotlight is introduced
        float m_innerCutoff;
        float m_outerCutoff;
        float m_attenuationConstant;
        float m_attenuationLinear;
        float m_attenuationQuadratic;
        Math::Vec3 m_diffuseIntensity;
        Math::Vec3 m_specularIntensity;
        Math::Vec3 m_position;
        Math::Vec3 m_color;
        Math::Vec3 m_direction;
        LightType m_lightType;
    };
}


#endif // SPACE__LIGHT_DATA__HPP