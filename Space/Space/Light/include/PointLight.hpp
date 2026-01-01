#ifndef SPACE__POINT_LIGHT__HPP
#define SPACE__POINT_LIGHT__HPP


#include "Light.hpp"
#include "../../Objects/include/LightObject.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Light/IPointLight.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API PointLight
		: public IPointLight
		, public Light
		, public LightObject
	{
	public:
		PointLight(
			const Math::Vec3& position, 
			const Math::Vec3& color = Math::Vec3{ 1.0f, 1.0f, 1.0f },
			float intensity = 1.0f,
			const Math::Vec3& ambient = Math::Vec3{ 0.1f, 0.1f, 0.1f },
			const Math::Vec3& diffuse = Math::Vec3{ 1.0f, 1.0f, 1.0f },
			const Math::Vec3& specular = Math::Vec3{ 1.0f, 1.0f, 1.0f },
			float attenuationConstant = 1.0f,
			float attenuationLinear = 0.1f,
			float attenuationQuadratic = 0.01f,
			float shadowNearPlane = 0.1f,
			float shadowFarPlane = 25.0f
		);
		~PointLight() override;

		// Getters
		float GetAttenuationConstant() const override;
		float GetAttenuationLinear() const override;
		float GetAttenuationQuadratic() const override;
		float GetShadowNearPlane() const override;
		float GetShadowFarPlane() const override;
		const Math::Vec3& GetPosition() const override;
		// Setters
		void SetAttenuationConstant(float attenuationConstant) override;
		void SetAttenuationLinear(float attenuationLinear) override;
		void SetAttenuationQuadratic(float attenuationQuadratic) override;
		void SetShadowNearPlane(float shadowNearPlane) override;
		void SetShadowFarPlane(float shadowFarPlane) override;
		void SetPosition(const Math::Vec3& position) override;

	private:
		float m_attenuationConstant;
		float m_attenuationLinear;
		float m_attenuationQuadratic;
		float m_shadowNearPlane;
		float m_shadowFarPlane;
		Math::Vec3 m_position;
	};
}


#endif // SPACE__POINT_LIGHT__HPP