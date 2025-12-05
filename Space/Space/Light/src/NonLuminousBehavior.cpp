#include "../include/NonLuminousBehavior.hpp"


namespace Andromeda::Space
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

	const Material& NonLuminousBehavior::GetMaterial() const
	{
		return m_material;
	}

	void NonLuminousBehavior::SetMaterial(const IMaterial& material)
	{
		const Material* concrete = dynamic_cast<const Material*>(&material);
		if (concrete != nullptr)
		{
			m_material = *concrete;
			return;
		}
	}
}
