#ifndef RENDERING__DIRECTIONAL_LIGHT__HPP
#define RENDERING__DIRECTIONAL_LIGHT__HPP


#include "Light.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(
			const glm::vec3& direction,
			const glm::vec3& color = glm::vec3{ 1.0f },
			float intensity = 1.0f
		);
		~DirectionalLight();

		// Getters
		glm::vec3 GetDirection() const;
		// Setters
		void SetDirection(const glm::vec3& direction);

	private:
		glm::vec3 m_direction;
	};
}


#endif // RENDERING__DIRECTIONAL_LIGHT__HPP