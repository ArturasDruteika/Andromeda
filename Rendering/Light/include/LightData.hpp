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
			~LightData();

			// Geters
			float GetIntensity() const;
			float GetRange() const;
			float GetInnerCutoff() const;
			float GetOuterCutoff() const;
			LightType GetLightType() const;
			glm::vec3 GetPosition() const;
			glm::vec3 GetColor() const;
			glm::vec3 GetDirection() const;
			glm::vec3 GetAttenuation() const;
			// Setters
			void SetIntensity(float intensity);
			void SetRange(float range);
			void SetInnerCutoff(float innertCutoff);
			void SetOuterCutoff(float outerCutoff);
			void SetLightType(const LightType& lightType);
			void SetPosition(const glm::vec3& position);
			void SetColor(const glm::vec3& color);
			void SetDirection(const glm::vec3& direction);
			void SetAttenuation(const glm::vec3& attenuation);

		private:
			float m_intensity;
			float m_range;
			float m_innerCutoff;
			float m_outerCutoff;
			LightType m_lightType;
			glm::vec3 m_position;
			glm::vec3 m_color;
			glm::vec3 m_direction;
			glm::vec3 m_attenuation;
		};
	}
}


#endif // RENDERING__LIGHT_DATA__HPP