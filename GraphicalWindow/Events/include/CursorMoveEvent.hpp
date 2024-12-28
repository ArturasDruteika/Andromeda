#ifndef GRAPHICAL_WINDOW__CURSOR_MOVE_EVENT_TYPE__HPP
#define GRAPHICAL_WINDOW__CURSOR_MOVE_EVENT_TYPE__HPP


#include "Event.hpp"
#include "EventType.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class CursorMoveEvent : public Event
		{
		public:
			CursorMoveEvent();
			~CursorMoveEvent();

		protected:
		};
	}
}


#endif // GRAPHICAL_WINDOW__CURSOR_MOVE_EVENT_TYPE__HPP