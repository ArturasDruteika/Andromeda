#ifndef SPACE__LIGHT__HPP
#define SPACE__LIGHT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Light/ILight.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API Light
		: public ILight
	{
	public:
		Light(
			const Math::Vec3& color,
			float intensity,
			const Math::Vec3& ambient,
			const Math::Vec3& diffuse,
			const Math::Vec3& specular
		);
		virtual ~Light() override;

		// Getters
		float GetIntensity() const override;
		Math::Vec3 GetColor() const override;
		Math::Vec3 GeAmbient() const override;
		Math::Vec3 GetDiffuse() const override;
		Math::Vec3 GetSpecular() const override;
		// Setters
		void SetIntensity(float intensity) override;
		void SetColor(const Math::Vec3& color) override;
		void SetAmbient(const Math::Vec3& ambient) override;
		void SetDiffuse(const Math::Vec3& diffuse) override;
		void SetSpecular(const Math::Vec3& specular) override;

	private:
		float m_intensity;
		Math::Vec3 m_color;
		Math::Vec3 m_ambient;
		Math::Vec3 m_diffuse;
		Math::Vec3 m_specular;
	};
}


#endif // SPACE__LIGHT__HPP