#include "../include/LuminousBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		LuminousBehavior::LuminousBehavior()
		{
		}

		LuminousBehavior::LuminousBehavior(const LightData& lightData)
		{
			m_lightData = lightData;
		}

		LuminousBehavior::~LuminousBehavior() = default;

		LightData LuminousBehavior::GetLightData() const
		{
			return m_lightData;
		}
	}
}
