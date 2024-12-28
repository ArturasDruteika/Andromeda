#include "KeyPressEvent.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		KeyPressEvent::KeyPressEvent()
		{
			m_eventType = EventType::KEYBOARD_PRESS;
		}

		KeyPressEvent::~KeyPressEvent()
		{
		}
	}
}