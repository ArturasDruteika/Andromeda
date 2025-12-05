#include "../include/PointLight.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Space
{
    PointLight::PointLight(
        const Math::Vec3& position, 
        const Math::Vec3& color, 
        float intensity, 
        const Math::Vec3& ambient,
        const Math::Vec3& diffuse,
        const Math::Vec3& specular,
        float attenuationConstant, 
        float attenuationLinear, 
        float attenuationQuadratic,
        float shadowNearPlane,
        float shadowFarPlane
    )
        : LuminousBehavior{ 
            Light{
                color,
                intensity,
                ambient,
                diffuse,
                specular
            },
            LightType::Point
        }
        , m_attenuationConstant{ attenuationConstant }
        , m_attenuationLinear{ attenuationLinear }
        , m_attenuationQuadratic{ attenuationQuadratic }
        , m_position{ position }
        , m_shadowNearPlane{ shadowNearPlane }
        , m_shadowFarPlane{ shadowFarPlane }
    {
    }

    PointLight::~PointLight() = default;

    float PointLight::GetAttenuationConstant() const
    {
        return m_attenuationConstant;
    }

    float PointLight::GetAttenuationLinear() const
    {
        return m_attenuationLinear;
    }

    float PointLight::GetAttenuationQuadratic() const
    {
        return m_attenuationQuadratic;
    }

    float PointLight::GetShadowNearPlane() const
    {
        return m_shadowNearPlane;
    }

    float PointLight::GetShadowFarPlane() const
    {
        return m_shadowFarPlane;
    }

    Math::Vec3 PointLight::GetPosition() const
    {
        return m_position;
    }

    void PointLight::SetAttenuationConstant(float constant)
    {
        if (constant < 0.0f)
        {
            spdlog::error("Attenuation constant must be non-negative");
            return;
        }
        m_attenuationConstant = constant;
    }

    void PointLight::SetAttenuationLinear(float linear)
    {
        if (linear < 0 || linear > 1)
        {
            spdlog::error("Attenuation linear components must be between 0.0 and 1.0");
            return;
        }
        m_attenuationLinear = linear;
    }

    void PointLight::SetAttenuationQuadratic(float quadratic)
    {
        if (quadratic < 0 || quadratic > 1)
        {
            spdlog::error("Attenuation quadratic components must be between 0.0 and 1.0");
            return;
        }
        m_attenuationQuadratic = quadratic;
    }

    void PointLight::SetShadowNearPlane(float shadowNearPlane)
    {
        m_shadowNearPlane = shadowNearPlane;
    }

    void PointLight::SetShadowFarPlane(float shadowFarPlane)
    {
        m_shadowFarPlane = shadowFarPlane;
    }

    void PointLight::SetPosition(const Math::Vec3& position)
    {
        m_position = position;
    }
}
