#include "../include/LuminousBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		//LuminousBehavior::LuminousBehavior()
		//	: m_light{ glm::vec3(1.0f), 1.0f, LightType::None }
		//{
		//}

		LuminousBehavior::LuminousBehavior(Light* light)
			: m_light{ light }
		{
		}

		LuminousBehavior::~LuminousBehavior() = default;

		Light* LuminousBehavior::GetLight() const
		{
			return m_light;
		}
	}
}