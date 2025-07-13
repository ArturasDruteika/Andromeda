#ifndef RENDERING__POINT_LIGHT__HPP
#define RENDERING__POINT_LIGHT__HPP


#include "Light.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class PointLight : public Light
	{
	public:
		PointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3{ 1.0f }, float intensity = 1.0f);
		~PointLight();

		// Getters
		float GetAttenuationConstant() const;
		float GetAttenuationLinear() const;
		float GetAttenuationQuadratic() const;
		glm::vec3 GetPosition() const;
		// Setters
		void SetAttenuationConstant(float attenuationConstant);
		void SetAttenuationLinear(float attenuationLinear);
		void SetAttenuationQuadratic(float attenuationQuadratic);
		void SetPosition(const glm::vec3& position);

	private:
		float m_attenuationConstant;
		float m_attenuationLinear;
		float m_attenuationQuadratic;
		glm::vec3 m_position;
	};
}


#endif // RENDERING__POINT_LIGHT__HPP