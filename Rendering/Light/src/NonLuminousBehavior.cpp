#include "../include/NonLuminousBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		NonLuminousBehavior::NonLuminousBehavior()
			: m_shininess{ 1.0f }
			, m_ambientReflectivity{ 1.0f }
			, m_specularStrength{ 0.05f }
			, m_diffuseStrength{ 1.0f }
		{
		}

		NonLuminousBehavior::NonLuminousBehavior(
			float shininess,
			float ambientReflectivity,
			float specularStrength,
			float diffuseStrength
		)
		{
			m_shininess = shininess;
			m_ambientReflectivity = ambientReflectivity;
			m_specularStrength = specularStrength;
			m_diffuseStrength = diffuseStrength;
		}

		NonLuminousBehavior::~NonLuminousBehavior() = default;

		float NonLuminousBehavior::GetShininess() const
		{
			return m_shininess;
		}

		float NonLuminousBehavior::GetAmbientReflectivity() const
		{
			return m_ambientReflectivity;
		}

		float NonLuminousBehavior::GetSpecularStrength() const
		{
			return m_specularStrength;
		}

		float NonLuminousBehavior::GetDiffuseStrength() const
		{
			return m_diffuseStrength;
		}

		void NonLuminousBehavior::SetShininess(float shininess)
		{
			m_shininess = shininess;
		}

		void NonLuminousBehavior::SetAmbientReflectivity(float ambientReflectivity)
		{
			m_ambientReflectivity = ambientReflectivity;
		}

		void NonLuminousBehavior::SetSpecularStrength(float specularStrength)
		{
			m_specularStrength = specularStrength;
		}

		void NonLuminousBehavior::SetDiffuseStrength(float diffuseStrength)
		{
			m_diffuseStrength = diffuseStrength;
		}
	}
}
