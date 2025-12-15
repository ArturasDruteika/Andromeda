#include "../include/LightObject.hpp"


namespace Andromeda::Space
{
	LightObject::LightObject(const LightType& lightType)
		: m_lightType{ lightType }
	{
	}

	LightObject::~LightObject() = default;

	const LightType& LightObject::GetLightType() const
	{
		return m_lightType;
	}
}