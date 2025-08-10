#include "../include/Light.hpp"


namespace Andromeda::Rendering
{
	Light::Light(
		const glm::vec3 color, 
		float intensity, 
		const glm::vec3& ambient, 
		const glm::vec3& diffuse,
		const glm::vec3& specular
	)
		: m_intensity{ intensity }
		, m_color{ color }
		, m_ambient{ ambient }
		, m_diffuse{ diffuse }
		, m_specular{ specular }
	{
	}

	Light::~Light() = default;

	float Light::GetIntensity() const
	{
		return m_intensity;
	}

	glm::vec3 Light::GetColor() const
	{
		return m_color;
	}

	glm::vec3 Light::GeAmbient() const
	{
		return m_ambient;
	}

	glm::vec3 Light::GetDiffuse() const
	{
		return m_diffuse;
	}

	glm::vec3 Light::GetSpecular() const
	{
		return m_specular;
	}

	void Light::SetIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::SetColor(const glm::vec3& color)
	{
		m_color = color;
	}

	void Light::SetAmbient(const glm::vec3& ambient)
	{
		m_ambient = ambient;
	}

	void Light::SetDiffuse(const glm::vec3& diffuse)
	{
		m_diffuse = diffuse;
	}

	void Light::SetSpecular(const glm::vec3& specular)
	{
		m_specular = specular;
	}
}
