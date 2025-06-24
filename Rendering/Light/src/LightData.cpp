#include "../include/LightData.hpp"
#include <glm/gtc/epsilon.hpp>


namespace Andromeda
{
	namespace Rendering
	{
		LightData::LightData()
			: m_lightType{ LightType::None }
			, m_color{ 1.0f }
			, m_intensity{ 1.0f }
			, m_position{ 0.0f }
			, m_range{ 100.0f }
			, m_direction{ 0.0f, -1.0f, 0.0f }
			, m_innerCutoff{ glm::cos(glm::radians(12.5f)) }
			, m_attenuation{ 1.0f, 0.09f, 0.032f }
			, m_outerCutoff{ glm::cos(glm::radians(17.5f)) }
		{
		}

        LightData::LightData(
            float intensity, 
            float range, 
            float innerCutoff, 
            float outerCutoff, 
            const LightType& lightType, 
            const glm::vec3& position, 
            const glm::vec3& color, 
            const glm::vec3& direction, 
            const glm::vec3& attenuation
        )
			: m_intensity{ intensity }
			, m_range{ range }
			, m_innerCutoff{ innerCutoff }
			, m_outerCutoff{ outerCutoff }
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
            if (linear < 0.0f || linear > 1.0f)
            {
                spdlog::error(
                    "Attenuation linear must be between 0.0 and 1.0 (inclusive), got {}",
                    linear
                );
                return;
            }
            m_attenuationLinear = linear;
        }

        void LightData::SetAttenuationQuadratic(float quadratic)
        {
            if (quadratic < 0.0f || quadratic > 1.0f)
            {
                spdlog::error(
                    "Attenuation quadratic must be between 0.0 and 1.0 (inclusive), got {}",
                    quadratic
                );
                return;
            }
            m_attenuationQuadratic = quadratic;
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
                spdlog::error("Direction vector must be non-zero");
            m_direction = glm::normalize(direction);
        }
	}
}
