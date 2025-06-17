#include "../include/NonLuminousBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		NonLuminousBehavior::NonLuminousBehavior()
			: m_shininess{ 1.0f }
			, m_specularStrength{ 0.05f }
			, m_diffuseStrength{ 0.001f }
		{
		}

		NonLuminousBehavior::NonLuminousBehavior(
			float shininess,
			float specularStrength,
			float diffuseStrength
		)
		{
			m_shininess = shininess;
			m_specularStrength = specularStrength;
			m_diffuseStrength = diffuseStrength;
		}

		NonLuminousBehavior::~NonLuminousBehavior() = default;

		float NonLuminousBehavior::GetShininess() const
		{
			return m_shininess;
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
