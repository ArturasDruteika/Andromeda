#include "../include/LuminousBehavior.hpp"
#include "../../LightTypes/include/DirectionalLight.hpp"
#include "../../LightTypes/include/PointLight.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		LuminousBehavior::LuminousBehavior(Light* light)
			: m_light{ light }
		{
			AssignLightType(light);
		}

		LuminousBehavior::~LuminousBehavior() = default;

		LightType LuminousBehavior::GetType() const
		{
			return m_type;
		}

		Light* LuminousBehavior::GetLight() const
		{
			return m_light;
		}

		void LuminousBehavior::AssignLightType(const Light* light)
		{
			if (dynamic_cast<const DirectionalLight*>(light))
			{
				m_type = LightType::Directional;
			}
			else if (dynamic_cast<const PointLight*>(light))
			{
				m_type = LightType::Point;
			}
			else
			{
				m_type = LightType::None;
			}
		}
	}
}