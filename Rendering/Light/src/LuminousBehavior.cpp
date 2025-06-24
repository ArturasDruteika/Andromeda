#include "../include/LuminousBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		LuminousBehavior::LuminousBehavior()
			: m_attenuationConstant{ 1.0f }
			, m_attenuationLinear{ 0.05f }
			, m_attenuationQuadratic{ 0.001f }
		{
		}

		LuminousBehavior::LuminousBehavior(
			float attenuationConstant, 
			float attenuationLinear, 
			float attenuationQuadratic
		)
		{
			m_attenuationConstant = attenuationConstant;
			m_attenuationLinear = attenuationLinear;
			m_attenuationQuadratic = attenuationQuadratic;
		}

		LuminousBehavior::LuminousBehavior(
			float attenuationConstant, 
			float attenuationLinear, 
			float attenuationQuadratic, 
			const LightData& lightData
		)
		{
			m_attenuationConstant = attenuationConstant;
			m_attenuationLinear = attenuationLinear;
			m_attenuationQuadratic = attenuationQuadratic;
			m_lightData = lightData;
		}

		LuminousBehavior::~LuminousBehavior() = default;

		float LuminousBehavior::GetAttenuationConstant() const
		{
			return m_attenuationConstant;
		}

		float LuminousBehavior::GetAttenuationLinear() const
		{
			return m_attenuationLinear;
		}

		float LuminousBehavior::GetAttenuationQuadratic() const
		{
			return m_attenuationQuadratic;
		}

		LightData LuminousBehavior::GetLightData() const
		{
			return m_lightData;
		}

		void LuminousBehavior::SetAttenuationConstant(float attenuationConstant)
		{
			m_attenuationConstant = attenuationConstant;
		}

		void LuminousBehavior::SetAttenuationLinear(float attenuationLinear)
		{
			m_attenuationLinear = attenuationLinear;
		}

		void LuminousBehavior::SetAttenuationQuadratic(float attenuationQuadratic)
		{
			m_attenuationQuadratic = attenuationQuadratic;
		}
	}
}
