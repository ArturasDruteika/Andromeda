#include "../include/LuminousObjectOpenGLBase.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		LuminousObjectOpenGLBase::LuminousObjectOpenGLBase()
			: m_attenuationConstant{ 1.0f }
			, m_attenuationLinear{ 0.1f }
			, m_attenuationQuadratic{ 0.01f }
		{
		}

		LuminousObjectOpenGLBase::LuminousObjectOpenGLBase(float attenuationConstant, float attenuationLinear, float attenuationQuadratic)
			: m_attenuationConstant{ attenuationConstant }
			, m_attenuationLinear{ attenuationLinear }
			, m_attenuationQuadratic{ attenuationQuadratic }
		{
		}

		LuminousObjectOpenGLBase::~LuminousObjectOpenGLBase()
		{
		}

		float LuminousObjectOpenGLBase::GetAttenuationConstant() const
		{
			return m_attenuationConstant;
		}

		float LuminousObjectOpenGLBase::GetAttenuationLinear() const
		{
			return m_attenuationLinear;
		}

		float LuminousObjectOpenGLBase::GetAttenuationQuadratic() const
		{
			return m_attenuationQuadratic;
		}

		void LuminousObjectOpenGLBase::SetAttenuationConstant(float attenuationConstant)
		{
			m_attenuationConstant = attenuationConstant;
		}

		void LuminousObjectOpenGLBase::SetAttenuationLinear(float attenuationLinear)
		{
			m_attenuationLinear = attenuationLinear;
		}
		
		void LuminousObjectOpenGLBase::SetAttenuationQuadratic(float attenuationQuadratic)
		{
			m_attenuationQuadratic = m_attenuationQuadratic;
		}
	}
}
