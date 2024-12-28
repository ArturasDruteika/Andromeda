#include "CursorMoveEvent.hpp"
#include "EventType.hpp"


namespace Andromeda
{
	namespace GraphicalWindow 
	{
		CursorMoveEvent::CursorMoveEvent()
		{
			m_eventType = EventType::CURSOR_MOVE;
		}

		CursorMoveEvent::~CursorMoveEvent()
		{
		}
	}
}