#include "../include/EventDispatcher.hpp"
#include "../include/Event.hpp"


namespace Andromeda
{
	namespace Window
	{
		EventDispatcher::EventDispatcher(Event& event)
			: m_event{ event }
		{
		}
	}
}

