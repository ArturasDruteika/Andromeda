#ifndef PHYSICAL_PROPERTIES__LIGHT__HPP
#define PHYSICAL_PROPERTIES__LIGHT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Support/include/LightTypes.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::PhysicalProperties
{
	class PHYSICAL_PROPERTIES_API Light
	{
	public:
		Light(
			const Math::Vec3& color,
			float intensity,
			const Math::Vec3& ambient,
			const Math::Vec3& diffuse,
			const Math::Vec3& specular
		);
		virtual ~Light();

		// Getters
		float GetIntensity() const;
		Math::Vec3 GetColor() const;
		Math::Vec3 GeAmbient() const;
		Math::Vec3 GetDiffuse() const;
		Math::Vec3 GetSpecular() const;
		// Setters
		void SetIntensity(float intensity);
		void SetColor(const Math::Vec3& color);
		void SetAmbient(const Math::Vec3& ambient);
		void SetDiffuse(const Math::Vec3& diffuse);
		void SetSpecular(const Math::Vec3& specular);

	private:
		float m_intensity;
		Math::Vec3 m_color;
		Math::Vec3 m_ambient;
		Math::Vec3 m_diffuse;
		Math::Vec3 m_specular;
	};
}


#endif // PHYSICAL_PROPERTIES__LIGHT__HPP