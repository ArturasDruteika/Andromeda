#ifndef RENDERING__LIGHT__HPP
#define RENDERING__LIGHT__HPP


#include "LightProperties.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class Light
	{
	public:
		Light(const glm::vec3 color, float intensity, const LightType& type);
		virtual ~Light();

		// Getters
		float GetIntensity() const;
		glm::vec3 GetColor() const;
		glm::vec3 GeAmbient() const;
		glm::vec3 GetDiffuse() const;
		glm::vec3 GetSpecular() const;
		LightType GetType() const;
		// Setters
		void SetIntensity(float intensity);
		void SetColor(const glm::vec3& color);
		void SetAmbient(const glm::vec3& ambient);
		void SetDiffuse(const glm::vec3& diffuse);
		void SetSpecular(const glm::vec3& specular);

	private:
		float m_intensity;
		glm::vec3 m_color;
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
		LightType m_type;
	};
}


#endif // RENDERING__LIGHT__HPP