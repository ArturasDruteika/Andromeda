#include "../include/EventBase.hpp"


namespace Andromeda::Window
{
	EventBase::EventBase()
		: m_handled{ false }
	{
	}

	EventBase::~EventBase() = default;

	bool EventBase::IsHandled() const
	{
		return m_handled;
	}

	void EventBase::SetHandled(bool handled)
	{
		m_handled = handled;
	}
}

