#include "../include/Materials.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda
{
	namespace Rendering
	{
		Material::Material()
			: m_shininess{ 0.6f }
			, m_name{ "emerald" }
			, m_ambient{ 0.0215,   0.1745,   0.0215 }
			, m_diffuse{ 0.07568,  0.61424,  0.07568 }
			, m_specular{ 0.633,    0.727811, 0.633 }
		{
		}

		Material::~Material()
		{
		}

		float Material::GetShininess() const
		{
			return m_shininess;
		}

		std::string Material::GetName() const
		{
			return m_name;
		}

		Math::Vec3 Material::GetAmbient() const
		{
			return m_ambient;
		}

		Math::Vec3 Material::GetDiffuse() const
		{
			return m_diffuse;
		}

		Math::Vec3 Material::GetSpecular() const
		{
			return m_specular;
		}

		void Material::SetShininess(float shininess)
		{
			m_shininess = shininess;
		}

		void Material::SetName(const std::string& name)
		{
			m_name = name;
		}

		void Material::SetAmbient(const Math::Vec3& ambient)
		{
			if (ValidateVec3Components(ambient))
				m_ambient = ambient;
			else
				spdlog::error("There are elements in ambient vector that are not in the range of [ 0.0f, 1.0f ]");
		}

		void Material::SetDiffuse(const Math::Vec3& diffuse)
		{
			if (ValidateVec3Components(diffuse))
				m_diffuse = diffuse;
			else
				spdlog::error("There are elements in diffuse vector that are not in the range of [ 0.0f, 1.0f ]");
		}

		void Material::SetSpecular(const Math::Vec3& specular)
		{
			if (ValidateVec3Components(specular))
				m_specular = specular;
			else
				spdlog::error("There are elements in specular vector that are not in the range of [ 0.0f, 1.0f ]");
		}

		bool Material::ValidateVec3Components(const Math::Vec3& vector)
		{
			return (vector[0] >= 0.0f && vector[0] <= 1.0f)
				&& (vector[1] >= 0.0f && vector[1] <= 1.0f)
				&& (vector[2] >= 0.0f && vector[2] <= 1.0f);
		}
	}
}
