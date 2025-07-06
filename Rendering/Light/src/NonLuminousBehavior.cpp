#include "../include/NonLuminousBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		NonLuminousBehavior::NonLuminousBehavior()
			: m_material{ Material() }
		{
		}

		NonLuminousBehavior::NonLuminousBehavior(
			float shininess,
			const std::string& name,
			const Math::Vec3& ambient,
			const Math::Vec3& specular,
			const Math::Vec3& diffuse
		)
		{
			m_material.shininess = shininess;
			m_material.name = name;
			m_material.ambient = ambient;
			m_material.specular = specular;
			m_material.diffuse = diffuse;
		}

		NonLuminousBehavior::NonLuminousBehavior(const Material& material)
			: m_material{ material }
		{
		}

		NonLuminousBehavior::~NonLuminousBehavior() = default;

		float NonLuminousBehavior::GetShininess() const
		{
			return m_material.shininess;
		}

		std::string NonLuminousBehavior::GetName() const
		{
			return m_material.name;
		}

		Math::Vec3 NonLuminousBehavior::GetAmbient() const
		{
			return m_material.ambient;
		}

		Math::Vec3 NonLuminousBehavior::GetSpecular() const
		{
			return m_material.specular;
		}

		Math::Vec3 NonLuminousBehavior::GetDiffuse() const
		{
			return m_material.diffuse;
		}

		void NonLuminousBehavior::SetShininess(float shininess)
		{
			m_material.shininess = shininess;
		}

		void NonLuminousBehavior::SetName(const std::string& name)
		{
			m_material.name = name;
		}

		void NonLuminousBehavior::SetAmbient(const Math::Vec3& ambient)
		{
			m_material.ambient = ambient;
		}

		void NonLuminousBehavior::SetSpecular(const Math::Vec3& specular)
		{
			m_material.specular = specular;
		}

		void NonLuminousBehavior::SetDiffuse(const Math::Vec3& diffuse)
		{
			m_material.diffuse = diffuse;
		}
	}
}
