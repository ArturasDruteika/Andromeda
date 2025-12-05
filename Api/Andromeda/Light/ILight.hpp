#ifndef ANDROMEDA__LIGHT_TYPES__HPP
#define ANDROMEDA__LIGHT_TYPES__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	class ILight
	{
	public:
		virtual ~ILight() = default;

		// Getters
		virtual float GetIntensity() const = 0;
		virtual Math::Vec3 GetColor() const = 0;
		virtual Math::Vec3 GeAmbient() const = 0;
		virtual Math::Vec3 GetDiffuse() const = 0;
		virtual Math::Vec3 GetSpecular() const = 0;
		// Setters
		virtual void SetIntensity(float intensity) = 0;
		virtual void SetColor(const Math::Vec3& color) = 0;
		virtual void SetAmbient(const Math::Vec3& ambient) = 0;
		virtual void SetDiffuse(const Math::Vec3& diffuse) = 0;
		virtual void SetSpecular(const Math::Vec3& specular) = 0;
	};
}


#endif // ANDROMEDA__LIGHT_TYPES__HPP