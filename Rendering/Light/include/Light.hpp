#ifndef RENDERING__LIGHT__HPP
#define RENDERING__LIGHT__HPP


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


#include "LightProperties.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API Light
	{
	public:
		Light(
			const glm::vec3 color,
			float intensity,
			const glm::vec3& ambient,
			const glm::vec3& diffuse,
			const glm::vec3& specular,
			const LightType& type
		);
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