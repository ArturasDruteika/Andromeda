#ifndef SPACE__DIRECTIONAL_LIGHT__HPP
#define SPACE__DIRECTIONAL_LIGHT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Abstracts/include/Light.hpp"
#include "../../Abstracts/include/LuminousBehavior.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API DirectionalLight
		: public LuminousBehavior
	{
	public:
		DirectionalLight(
			const Math::Vec3& direction,
			const Math::Vec3& color = Math::Vec3{ 1.0f, 1.0f, 1.0f },
			float intensity = 1.0f,
			const Math::Vec3& ambient = Math::Vec3{ 0.1f, 0.1f, 0.1f },
			const Math::Vec3& diffuse = Math::Vec3{ 0.4f, 0.4f, 0.4f },
			const Math::Vec3& specular = Math::Vec3{ 0.4f, 0.4f, 0.4f },
			float orthographicHalfSize = 10.0f,
			float nearPlane = 1.0f,
			float farPlane = 30.0f
		);
		~DirectionalLight();

		// Getters
		float GetLightOrthographicHalfSize() const;
		float GetLightNearPlane() const;
		float GetLightFarPlane() const;
		Math::Vec3 GetDirection() const;
		// Setters
		void SetLightOrthographicHalfSize(float halfSize);
		void SetLightNearPlane(float nearPlane);
		void SetLightFarPlane(float farPlane);
		void SetDirection(const Math::Vec3& direction);

	private:
		float m_orthographicHalfSize;
		float m_nearPlane;
		float m_farPlane;
		Math::Vec3 m_direction;
	};
}


#endif // SPACE__DIRECTIONAL_LIGHT__HPP