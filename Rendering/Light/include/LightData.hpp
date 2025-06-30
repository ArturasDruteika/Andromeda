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
			LightData(
				float intensity = 1.0f,
				float range = 100.0f,
				float innerCutoff = 12.5f,
				float outerCutoff = 17.5f,
				float attenuationConstant = 1.0f,
				float attenuationLinear = 0.05f,
				float attenuationQuadratic = 0.001f,
				float diffuseIntensity = 1.0f,
				float specularIntensity = 1.0f,
				const LightType& lightType = LightType::None,
				const glm::vec3& position = glm::vec3{ 0.0f },
				const glm::vec3& color = glm::vec3{ 1.0f },
				const glm::vec3& direction = glm::vec3{ 0.0f, -1.0f, 0.0f }
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
			float GetDiffuseIntensity() const;
			float GetSpecularIntensity() const;
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
			void SetDiffuseIntensity(float diffuseIntensity);
			void SetSpecularIntensity(float specularIntensity);
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
			float m_diffuseIntensity;
			float m_specularIntensity;
			LightType m_lightType;
			glm::vec3 m_position;
			glm::vec3 m_color;
			glm::vec3 m_direction;
		};
	}
}


#endif // RENDERING__LIGHT_DATA__HPP