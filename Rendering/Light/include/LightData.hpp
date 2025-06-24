#ifndef RENDERING__LIGHT_DATA__HPP
#define RENDERING__LIGHT_DATA__HPP


#include "LightProperties.hpp"
#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class LightData 
		{
		public:
			LightData();
			LightData(
				float intensity,
				float range,
				float innerCutoff,
				float outerCutoff,
				const LightType& lightType,
				const glm::vec3& position,
				const glm::vec3& color,
				const glm::vec3& direction,
				const glm::vec3& attenuation
			);
			~LightData();

			// Geters
			float GetIntensity() const;
			float GetRange() const;
			float GetInnerCutoff() const;
			float GetOuterCutoff() const;
			float GetAttenuationConstant() const;
			float GetAttenuationLinear() const;
			float GetAttenuationQuadratic() const;
			LightType GetLightType() const;
			glm::vec3 GetPosition() const;
			glm::vec3 GetColor() const;
			glm::vec3 GetDirection() const;
			// Setters
			void SetIntensity(float intensity);
			void SetRange(float range);
			void SetInnerCutoff(float innertCutoff);
			void SetOuterCutoff(float outerCutoff);
			void SetAttenuationConstant(float constant);
			void SetAttenuationLinear(float linear);
			void SetAttenuationQuadratic(float quadratic);
			void SetLightType(const LightType& lightType);
			void SetPosition(const glm::vec3& position);
			void SetColor(const glm::vec3& color);
			void SetDirection(const glm::vec3& direction);

		private:
			float m_intensity;
			float m_range;
			float m_innerCutoff;
			float m_outerCutoff;
			float m_attenuationConstant;
			float m_attenuationLinear;
			float m_attenuationQuadratic;
			LightType m_lightType;
			glm::vec3 m_position;
			glm::vec3 m_color;
			glm::vec3 m_direction;
		};
	}
}


#endif // RENDERING__LIGHT_DATA__HPP