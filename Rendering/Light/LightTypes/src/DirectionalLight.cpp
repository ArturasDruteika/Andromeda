#include "../include/DirectionalLight.hpp"


namespace Andromeda::Rendering
{
	DirectionalLight::DirectionalLight(
		const glm::vec3& direction,
		const glm::vec3& color,
		float intensity,
		const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		float orthographicHalfSize,
		float nearPlane,
		float farPlane
	)
		: LuminousBehavior{ Light{
				color,
				intensity,
				ambient,
				diffuse,
				specular
			}, 
			LightType::Directional 
		}
		, m_orthographicHalfSize{ orthographicHalfSize }
		, m_nearPlane{ nearPlane }
		, m_farPlane{ farPlane }
		, m_direction{ glm::normalize(direction) }
	{
	}

	DirectionalLight::~DirectionalLight() = default;

	float DirectionalLight::GetLightOrthographicHalfSize() const
	{
		return m_orthographicHalfSize;
	}

	float DirectionalLight::GetLightNearPlane() const
	{
		return m_nearPlane;
	}

	float DirectionalLight::GetLightFarPlane() const
	{
		return m_farPlane;
	}

	glm::vec3 DirectionalLight::GetDirection() const
	{
		return m_direction;
	}

	void DirectionalLight::SetLightOrthographicHalfSize(float halfSize)
	{
		if (halfSize > 0.0f)
			m_orthographicHalfSize = halfSize;
	}

	void DirectionalLight::SetLightNearPlane(float nearPlane)
	{
		if (nearPlane > 0.0f)
			m_nearPlane = nearPlane;
	}

	void DirectionalLight::SetLightFarPlane(float farPlane)
	{
		if (farPlane > m_nearPlane)
			m_farPlane = farPlane;
	}

	void DirectionalLight::SetDirection(const glm::vec3& direction)
	{
		m_direction = direction;
	}
}
