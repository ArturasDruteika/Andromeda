#include "../include/EventDispatcher.hpp"


namespace Andromeda::Window
{
	EventDispatcher::EventDispatcher(IEvent& event)
		: m_event{ event }
	{
	}

	EventDispatcher::~EventDispatcher() = default;
}

