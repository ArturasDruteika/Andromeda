#ifndef RENDERING__LUMINOUS_BEHAVIOR__HPP
#define RENDERING__LUMINOUS_BEHAVIOR__HPP


#include "pch.hpp"
#include "ILightBehavior.hpp"
#include "LightProperties.hpp"
#include "LightData.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class LuminousBehavior
			: public ILightBehavior
		{
		public:
			LuminousBehavior();
			LuminousBehavior(
				float attenuationConstant,
				float attenuationLinear,
				float attenuationQuadratic
			);
			LuminousBehavior(
				float attenuationConstant,
				float attenuationLinear,
				float attenuationQuadratic,
				const LightData& lightData
			);
			~LuminousBehavior();

			// Getters
			float GetAttenuationConstant() const;
			float GetAttenuationLinear() const;
			float GetAttenuationQuadratic() const;
			LightData GetLightData() const;
			// Setters
			void SetAttenuationConstant(float attenuationConstant);
			void SetAttenuationLinear(float attenuationLinear);
			void SetAttenuationQuadratic(float attenuationQuadratic);

		private:
			float m_attenuationConstant;
			float m_attenuationLinear;
			float m_attenuationQuadratic;

			LightData m_lightData;
		};
	}
}


#endif // RENDERING__LUMINOUS_BEHAVIOR__HPP