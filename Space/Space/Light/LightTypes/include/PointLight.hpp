#ifndef SPACE__POINT_LIGHT__HPP
#define SPACE__POINT_LIGHT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Abstracts/include/Light.hpp"
#include "../../Abstracts/include/LuminousBehavior.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API PointLight
		: public LuminousBehavior
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
		~PointLight();

		// Getters
		float GetAttenuationConstant() const;
		float GetAttenuationLinear() const;
		float GetAttenuationQuadratic() const;
		float GetShadowNearPlane() const;
		float GetShadowFarPlane() const;
		Math::Vec3 GetPosition() const;
		// Setters
		void SetAttenuationConstant(float attenuationConstant);
		void SetAttenuationLinear(float attenuationLinear);
		void SetAttenuationQuadratic(float attenuationQuadratic);
		void SetShadowNearPlane(float shadowNearPlane);
		void SetShadowFarPlane(float shadowFarPlane);
		void SetPosition(const Math::Vec3& position);

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