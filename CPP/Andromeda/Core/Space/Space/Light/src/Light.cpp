#include "../include/Light.hpp"


namespace Andromeda::Space
{
	Light::Light(
		const Math::Vec3& color, 
		float intensity, 
		const Math::Vec3& ambient, 
		const Math::Vec3& diffuse,
		const Math::Vec3& specular
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

	Math::Vec3 Light::GetColor() const
	{
		return m_color;
	}

	Math::Vec3 Light::GeAmbient() const
	{
		return m_ambient;
	}

	Math::Vec3 Light::GetDiffuse() const
	{
		return m_diffuse;
	}

	Math::Vec3 Light::GetSpecular() const
	{
		return m_specular;
	}

	void Light::SetIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::SetColor(const Math::Vec3& color)
	{
		m_color = color;
	}

	void Light::SetAmbient(const Math::Vec3& ambient)
	{
		m_ambient = ambient;
	}

	void Light::SetDiffuse(const Math::Vec3& diffuse)
	{
		m_diffuse = diffuse;
	}

	void Light::SetSpecular(const Math::Vec3& specular)
	{
		m_specular = specular;
	}
}
