#include "../include/EventDispatcher.hpp"
#include "../include/Event.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		EventDispatcher::EventDispatcher(Event& event)
			: m_event{ event }
		{
		}
	}
}

