#ifndef RENDERING__DIRECTIONAL_LIGHT__HPP
#define RENDERING__DIRECTIONAL_LIGHT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Abstracts/include/Light.hpp"
#include "../../Abstracts/include/LuminousBehavior.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API DirectionalLight
		: public Light
		, public LuminousBehavior
	{
	public:
		DirectionalLight(
			const glm::vec3& direction,
			const glm::vec3& color = glm::vec3{ 1.0f },
			float intensity = 1.0f,
			const glm::vec3& ambient = glm::vec3(0.1f),
			const glm::vec3& diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
			const glm::vec3& specular = glm::vec3(0.4f, 0.4f, 0.4f)
		);
		~DirectionalLight();

		// Getters
		float GetLightOrthographicHalfSize() const;
		float GetLightNearPlane() const;
		float GetLightFarPlane() const;
		glm::vec3 GetDirection() const;
		// Setters
		void SetLightOrthographicHalfSize(float halfSize);
		void SetLightNearPlane(float nearPlane);
		void SetLightFarPlane(float farPlane);
		void SetDirection(const glm::vec3& direction);

	private:
		float m_orthographicHalfSize;
		float m_nearPlane;
		float m_farPlane;
		glm::vec3 m_direction;
	};
}


#endif // RENDERING__DIRECTIONAL_LIGHT__HPP