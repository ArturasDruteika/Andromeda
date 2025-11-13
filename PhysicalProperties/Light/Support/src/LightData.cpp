#include "../include/LightData.hpp"
#include "LinearAlgebraOperations.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::PhysicalProperties
{
    LightData::LightData(
        float intensity,
        float range,
        float innerCutoff,
        float outerCutoff,
        float attenuationConstant,
        float attenuationLinear,
        float attenuationQuadratic,
        const Math::Vec3& diffuseIntensity,
        const Math::Vec3& specularIntensity,
        const Math::Vec3& position,
        const Math::Vec3& color,
        const Math::Vec3& direction,
        const LightType& lightType
    )
        : m_intensity{ intensity }
        , m_range{ range }
        , m_innerCutoff{ innerCutoff }
        , m_outerCutoff{ outerCutoff }
        , m_attenuationConstant{ attenuationConstant }
        , m_attenuationLinear{ attenuationLinear }
        , m_attenuationQuadratic{ attenuationQuadratic }
        , m_diffuseIntensity{ diffuseIntensity }
        , m_specularIntensity{ specularIntensity }
        , m_lightType{ lightType }
        , m_position{ position }
        , m_color{ color }
        , m_direction{ Math::LinAlgOps::Normalize(direction) }
    {
    }

    LightData::~LightData() = default;

    float LightData::GetIntensity() const 
    { 
        return m_intensity; 
    }

    float LightData::GetRange() const 
    { 
        return m_range;
    }

    float LightData::GetInnerCutoff() const
    {
        return m_innerCutoff;
    }

    float LightData::GetOuterCutoff() const
    {
        return m_outerCutoff;
    }

    float LightData::GetAttenuationConstant() const
    {
        return m_attenuationConstant;
    }

    float LightData::GetAttenuationLinear() const
    {
        return m_attenuationLinear;
    }

    float LightData::GetAttenuationQuadratic() const
    {
        return m_attenuationQuadratic;
    }

    Math::Vec3 LightData::GetDiffuseIntensity() const
    {
        return m_diffuseIntensity;
    }

    Math::Vec3 LightData::GetSpecularIntensity() const
    {
        return m_specularIntensity;
    }

    LightType LightData::GetLightType() const
    {
        return m_lightType;
    }

    Math::Vec3 LightData::GetPosition() const
    {
        return m_position;
    }

    Math::Vec3 LightData::GetColor() const
    {
        return m_color;
    }

    Math::Vec3 LightData::GetDirection() const
    {
        return m_direction;
    }


    void LightData::SetIntensity(float intensity)
    {
        if (intensity < 0.0f)
            spdlog::error("Intensity must be non-negative");
        m_intensity = intensity;
    }

    void LightData::SetRange(float range)
    {
        if (range <= 0.0f)
            spdlog::error("Range must be positive");
        m_range = range;
    }

    void LightData::SetInnerCutoff(float innerCutoff)
    {
        if (innerCutoff < 0.0f || innerCutoff > 1.0f)
            spdlog::error("Inner cutoff must be in [0, 1]");
        if (innerCutoff > m_outerCutoff)
            spdlog::error("Inner cutoff cannot exceed outer cutoff");
        m_innerCutoff = innerCutoff;
    }

    void LightData::SetOuterCutoff(float outerCutoff)
    {
        if (outerCutoff < 0.0f || outerCutoff > 1.0f)
            spdlog::error("Outer cutoff must be in [0, 1]");
        if (outerCutoff < m_innerCutoff)
            spdlog::error("Outer cutoff cannot be less than inner cutoff");
        m_outerCutoff = outerCutoff;
    }

    void LightData::SetAttenuationConstant(float constant)
    {
        if (constant < 0.0f)
            spdlog::error("Attenuation constant must be non-negative");
        m_attenuationConstant = constant;
    }

    void LightData::SetAttenuationLinear(float linear)
    {
        if (linear < 0 || linear > 1)
        {
            spdlog::error(
                "Attenuation linear components must be between 0.0 and 1.0"
            );
            return;
        }
        m_attenuationLinear = linear;
    }

    void LightData::SetAttenuationQuadratic(float quadratic)
    {
        if (quadratic < 0 || quadratic > 1)
        {
            spdlog::error(
                "Attenuation quadratic components must be between 0.0 and 1.0"
            );
            return;
        }
        m_attenuationQuadratic = quadratic;
    }

    void LightData::SetDiffuseIntensity(const Math::Vec3& diffuseIntensity)
    {
        m_diffuseIntensity = diffuseIntensity;
    }

    void LightData::SetSpecularIntensity(const Math::Vec3& specularIntensity)
    {
        m_specularIntensity = specularIntensity;
    }

    void LightData::SetLightType(const LightType& lightType)
    {
        m_lightType = lightType;
    }

    void LightData::SetPosition(const Math::Vec3& position)
    {
        m_position = position;
    }

    void LightData::SetColor(const Math::Vec3& color)
    {
        m_color = color;
    }

    void LightData::SetDirection(const Math::Vec3& direction)
    {
        float len2 = Math::LinAlgOps::DotProd(direction, direction);
        if (len2 < 1e-6f)
        {
            spdlog::error("Direction vector must be non-zero");
            return;
        }
        m_direction = Math::LinAlgOps::Normalize(direction);
    }
}
