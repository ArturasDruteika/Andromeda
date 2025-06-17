#ifndef RENDERING__LUMINOUS_BEHAVIOR__HPP
#define RENDERING__LUMINOUS_BEHAVIOR__HPP


#include "pch.hpp"
#include "ILightBehavior.hpp"


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
			~LuminousBehavior();

			// Getters
			float GetAttenuationConstant() const;
			float GetAttenuationLinear() const;
			float GetAttenuationQuadratic() const;
			// Setters
			void SetAttenuationConstant(float attenuationConstant);
			void SetAttenuationLinear(float attenuationLinear);
			void SetAttenuationQuadratic(float attenuationQuadratic);

		private:
			float m_attenuationConstant;
			float m_attenuationLinear;
			float m_attenuationQuadratic;
		};
	}
}


#endif // RENDERING__LUMINOUS_BEHAVIOR__HPP