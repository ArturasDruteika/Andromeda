#ifndef GRAPHICAL_WINDOW__CURSOR_MOVE_EVENT_TYPE__HPP
#define GRAPHICAL_WINDOW__CURSOR_MOVE_EVENT_TYPE__HPP


#include "Event.hpp"
#include "EventType.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class MouseMoveEvent : public Event
		{
		public:
			MouseMoveEvent();
			~MouseMoveEvent();

			double GetX() const;
			double GetY() const;

		private:
			double m_x;
			double m_y;
		};
	}
}


#endif // GRAPHICAL_WINDOW__CURSOR_MOVE_EVENT_TYPE__HPP