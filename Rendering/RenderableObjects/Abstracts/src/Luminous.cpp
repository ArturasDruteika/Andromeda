#include "../include/Luminous.hpp"
#include "../../../Light/Abstracts/include/LuminousBehavior.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
	Luminous::Luminous()
		: m_luminous{ false }
		, m_pILightBehavior{ nullptr }
	{
	}

	Luminous::~Luminous()
	{
		delete m_pILightBehavior;
		m_pILightBehavior = nullptr;
	}

	bool Luminous::IsLuminous() const
	{
		return m_luminous;
	}

	ILightBehavior* Luminous::GetLightBehavior() const
	{
		return m_pILightBehavior;
	}

	void Luminous::SetLuminousBehavior(ILightBehavior* behavior)
	{
		if (behavior == nullptr)
		{
			spdlog::error("Trying to set nullptr behavior.");
			return;
		}
		delete m_pILightBehavior;
		m_pILightBehavior = behavior;
		m_luminous = dynamic_cast<LuminousBehavior*>(m_pILightBehavior) ? true : false;
	}
}
