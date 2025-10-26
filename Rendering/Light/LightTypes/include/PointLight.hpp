#ifndef RENDERING__POINT_LIGHT__HPP
#define RENDERING__POINT_LIGHT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Abstracts/include/Light.hpp"
#include "../../Abstracts/include/LuminousBehavior.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API PointLight
		: public LuminousBehavior
	{
	public:
		PointLight(
			const glm::vec3& position, 
			const glm::vec3& color = glm::vec3{ 1.0f }, 
			float intensity = 1.0f,
			const glm::vec3& ambient = glm::vec3(0.1f),
			const glm::vec3& diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			const glm::vec3& specular = glm::vec3(1.0f, 1.0f, 1.0f),
			float attenuationConstant = 1.0f,
			float attenuationLinear = 0.1f,
			float attenuationQuadratic = 0.01f,
			float shadowNearPlane = 0.1f,
			float shadowFarPlane = 25.0f
		);
		~PointLight();

		// Getters
		float GetAttenuationConstant() const;
		float GetAttenuationLinear() const;
		float GetAttenuationQuadratic() const;
		float GetShadowNearPlane() const;
		float GetShadowFarPlane() const;
		glm::vec3 GetPosition() const;
		// Setters
		void SetAttenuationConstant(float attenuationConstant);
		void SetAttenuationLinear(float attenuationLinear);
		void SetAttenuationQuadratic(float attenuationQuadratic);
		void SetShadowNearPlane(float shadowNearPlane);
		void SetShadowFarPlane(float shadowFarPlane);
		void SetPosition(const glm::vec3& position);

	private:
		float m_attenuationConstant;
		float m_attenuationLinear;
		float m_attenuationQuadratic;
		float m_shadowNearPlane;
		float m_shadowFarPlane;
		glm::vec3 m_position;
	};
}


#endif // RENDERING__POINT_LIGHT__HPP