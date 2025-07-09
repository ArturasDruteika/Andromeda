#include "../include/LightData.hpp"
#include <glm/gtc/epsilon.hpp>


namespace Andromeda
{
	namespace Rendering
	{
        LightData::LightData(
            float intensity,
            float range,
            float innerCutoff,
            float outerCutoff,
            float attenuationConstant,
            float attenuationLinear,
            float attenuationQuadratic,
            const glm::vec3& diffuseIntensity,
            const glm::vec3& specularIntensity,
            const glm::vec3& position,
            const glm::vec3& color,
            const glm::vec3& direction,
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
            , m_direction{ glm::normalize(direction) }
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

        glm::vec3 LightData::GetDiffuseIntensity() const
        {
            return m_diffuseIntensity;
        }

        glm::vec3 LightData::GetSpecularIntensity() const
        {
            return m_specularIntensity;
        }

        LightType LightData::GetLightType() const
        {
            return m_lightType;
        }

        glm::vec3 LightData::GetPosition() const
        {
            return m_position;
        }

        glm::vec3 LightData::GetColor() const
        {
            return m_color;
        }

        glm::vec3 LightData::GetDirection() const
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

        void LightData::SetDiffuseIntensity(const glm::vec3& diffuseIntensity)
        {
            if (glm::any(glm::lessThan(diffuseIntensity, glm::vec3(0.0f))))
            {
                spdlog::error("Diffuse intensity components must be non-negative");
                return;
            }
            m_diffuseIntensity = diffuseIntensity;
        }

        void LightData::SetSpecularIntensity(const glm::vec3& specularIntensity)
        {
            if (glm::any(glm::lessThan(specularIntensity, glm::vec3(0.0f))))
            {
                spdlog::error("Specular intensity components must be non-negative");
                return;
            }
            m_specularIntensity = specularIntensity;
        }

        void LightData::SetLightType(const LightType& lightType)
        {
            m_lightType = lightType;
        }

        void LightData::SetPosition(const glm::vec3& position)
        {
            m_position = position;
        }

        void LightData::SetColor(const glm::vec3& color)
        {
            m_color = color;
        }

        void LightData::SetDirection(const glm::vec3& direction)
        {
            float len2 = glm::dot(direction, direction);
            if (len2 < 1e-6f)
            {
                spdlog::error("Direction vector must be non-zero");
                return;
            }
            m_direction = glm::normalize(direction);
        }
	}
}
