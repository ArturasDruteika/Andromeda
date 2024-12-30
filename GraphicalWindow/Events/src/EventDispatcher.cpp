#include "../include/EventDispatcher.hpp"
#include "../include/Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		EventDispatcher::EventDispatcher(Event& event)
			: m_event(event)
		{
		}
	}
}

