#include "../include/DirectionalLight.hpp"


namespace Andromeda::Rendering
{
	DirectionalLight::DirectionalLight(
		const glm::vec3& direction, 
		const glm::vec3& color, 
		float intensity
	)
		: Light(color, intensity, LightType::Directional)
		, m_direction{ glm::normalize(direction) }
	{
	}

	DirectionalLight::~DirectionalLight() = default;

	glm::vec3 DirectionalLight::GetDirection() const
	{
		return m_direction;
	}

	void DirectionalLight::SetDirection(const glm::vec3& direction)
	{
		m_direction = direction;
	}
}
