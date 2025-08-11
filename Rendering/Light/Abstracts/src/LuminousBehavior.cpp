#include "../include/LuminousBehavior.hpp"
#include "../../LightTypes/include/DirectionalLight.hpp"
#include "../../LightTypes/include/PointLight.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		LuminousBehavior::LuminousBehavior(Light* light, const LightType& type)
			: m_light{ light }
			, m_type{ type }
		{
		}

		LuminousBehavior::~LuminousBehavior()
		{
			delete m_light;
			m_light = nullptr;
			m_type = LightType::None;
		};

		LightType LuminousBehavior::GetType() const
		{
			return m_type;
		}

		Light* LuminousBehavior::GetLight() const
		{
			return m_light;
		}
	}
}