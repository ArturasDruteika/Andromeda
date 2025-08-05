#ifndef RENDERING__POINT_LIGHT__HPP
#define RENDERING__POINT_LIGHT__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "../../Abstracts/include/Light.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API PointLight : public Light
	{
	public:
		PointLight(
			const glm::vec3& position, 
			const glm::vec3& color = glm::vec3{ 1.0f }, 
			float intensity = 1.0f,
			const glm::vec3& ambient = glm::vec3(0.1f),
			const glm::vec3& diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
			const glm::vec3& specular = glm::vec3(0.4f, 0.4f, 0.4f),
			float attenuationConstant = 1.0f,
			float attenuationLinear = 0.1f,
			float attenuationQuadratic = 0.01f
		);
		~PointLight();

		// Getters
		float GetAttenuationConstant() const;
		float GetAttenuationLinear() const;
		float GetAttenuationQuadratic() const;
		glm::vec3 GetPosition() const;
		// Setters
		void SetAttenuationConstant(float attenuationConstant);
		void SetAttenuationLinear(float attenuationLinear);
		void SetAttenuationQuadratic(float attenuationQuadratic);
		void SetPosition(const glm::vec3& position);

	private:
		float m_attenuationConstant;
		float m_attenuationLinear;
		float m_attenuationQuadratic;
		glm::vec3 m_position;
	};
}


#endif // RENDERING__POINT_LIGHT__HPP