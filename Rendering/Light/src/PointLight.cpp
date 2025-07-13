#include "../include/PointLight.hpp"


namespace Andromeda::Rendering
{
	PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity)
		: Light(color, intensity, LightType::Point)
        , m_position{ position }
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

    glm::vec3 PointLight::GetPosition() const
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

    void PointLight::SetPosition(const glm::vec3& position)
    {
        m_position = position;
    }
}
