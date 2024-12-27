#include "Event.hpp"


namespace Andromeda
{
	namespace Window
	{
		Event::Event()
		{
		}

		Event::~Event()
		{
		}

		EventType Event::GetEventType() const
		{
			return m_eventType;
		}
	}
}

