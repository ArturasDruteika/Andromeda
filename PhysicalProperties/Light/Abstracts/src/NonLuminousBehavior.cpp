#include "../include/NonLuminousBehavior.hpp"


namespace Andromeda::PhysicalProperties
{
	NonLuminousBehavior::NonLuminousBehavior()
		: m_material{ Material() }
	{
	}

	NonLuminousBehavior::NonLuminousBehavior(const Material& material)
		: m_material{ material }
	{
	}

	NonLuminousBehavior::~NonLuminousBehavior() = default;

	Material NonLuminousBehavior::GetMaterial()
	{
		return m_material;
	}

	void NonLuminousBehavior::SetMaterial(const Material& material)
	{
		m_material = material;
	}
}
