#include "Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		Event::Event()
		{
		}

		Event::~Event()
		{
		}

		std::string Event::GetEventType() const
		{
			return m_eventType;
		}
	}
}

