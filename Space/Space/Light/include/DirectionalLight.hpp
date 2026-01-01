#ifndef SPACE__DIRECTIONAL_LIGHT__HPP
#define SPACE__DIRECTIONAL_LIGHT__HPP


#include "Light.hpp"
#include "../../Objects/include/LightObject.hpp"
#include "../../Transformations/include/Rotatable.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Light/IDirectionalLight.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API DirectionalLight
		: public Light
		, public LightObject
		, public Rotatable
		, public virtual IDirectionalLight

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
		~DirectionalLight() override;

		// Getters
		float GetLightOrthographicHalfSize() const override;
		float GetLightNearPlane() const override;
		float GetLightFarPlane() const override;
		const Math::Vec3& GetDirection() const override;
		// Setters
		void SetLightOrthographicHalfSize(float halfSize) override;
		void SetLightNearPlane(float nearPlane) override;
		void SetLightFarPlane(float farPlane) override;
		void SetDirection(const Math::Vec3& direction) override;

	private:
		float m_orthographicHalfSize;
		float m_nearPlane;
		float m_farPlane;
		Math::Vec3 m_direction;
	};
}


#endif // SPACE__DIRECTIONAL_LIGHT__HPP