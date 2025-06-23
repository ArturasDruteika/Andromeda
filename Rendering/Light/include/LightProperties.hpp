#ifndef RENDERING__LIGHT_PROPERTIES__HPP
#define RENDERING__LIGHT_PROPERTIES__HPP


#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		enum class LightType : int
		{
			None = 0,
			Directional = 1,
			Point = 2,
			Spot = 3
		};

		struct LightData {
			LightType type = LightType::None;
			glm::vec3 color = glm::vec3{ 1.f, 1.0f, 1.0f };
			float intensity = 1.0f;
			float range = 100.0f;
			float innerCutoff = glm::cos(glm::radians(12.5f));
			float outerCutoff = glm::cos(glm::radians(17.5f));
			glm::vec3 position = glm::vec3{ 0.0f, 0.0f, 0.0f };
			glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
			glm::vec3 attenuation = glm::vec3(1.0f, 0.09f, 0.032f);

			LightData()
				: type(LightType::None)
				, color(1.0f)
				, intensity(1.0f)
				, position(0.0f)
				, range(100.0f)
				, direction(0.0f, -1.0f, 0.0f)
				, innerCutoff(glm::cos(glm::radians(12.5f)))
				, attenuation(1.0f, 0.09f, 0.032f)
				, outerCutoff(glm::cos(glm::radians(17.5f)))
			{
			}
		};
	}
}


#endif // RENDERING__LIGHT_PROPERTIES__HPP