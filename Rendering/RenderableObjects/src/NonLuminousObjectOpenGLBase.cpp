#include "../include/NonLuminousObjectOpenGLBase.hpp"

namespace Andromeda
{
	namespace Rendering
	{
		NonLuminousObjectOpenGLBase::NonLuminousObjectOpenGLBase()
			: m_shininess{ 32.0f }
			, m_specularStrength{ 0.5f }
			, m_diffuseStrength{ 0.5f }
		{
		}

		NonLuminousObjectOpenGLBase::NonLuminousObjectOpenGLBase(float shininess, float specularStrength, float diffuseStrength)
		{
		}

		NonLuminousObjectOpenGLBase::~NonLuminousObjectOpenGLBase() = default;

		float NonLuminousObjectOpenGLBase::GetShininess() const
		{
			return m_shininess;
		}

		float NonLuminousObjectOpenGLBase::GetSpecularStrength() const
		{
			return m_specularStrength;
		}

		float NonLuminousObjectOpenGLBase::GetDiffuseStrength() const
		{
			return m_diffuseStrength;
		}

		void NonLuminousObjectOpenGLBase::SetShininess(float shininess)
		{
			m_shininess = shininess;
		}

		void NonLuminousObjectOpenGLBase::SetSpecularStrength(float specularStrength)
		{
			m_specularStrength = specularStrength;
		}

		void NonLuminousObjectOpenGLBase::SetDiffuseStrength(float diffuseStrength)
		{
			m_diffuseStrength = diffuseStrength;
		}


	}
}
