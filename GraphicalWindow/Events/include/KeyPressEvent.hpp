#ifndef GRAPHICAL_WINDOW__KEY_PRESS_EVENT__HPP
#define GRAPHICAL_WINDOW__KEY_PRESS_EVENT__HPP


#include "EventType.hpp"
#include "Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class KeyPressEvent : public Event
		{
		public:
			KeyPressEvent();
			~KeyPressEvent();

		protected:
		};
	}
}


#endif // GRAPHICAL_WINDOW__KEY_PRESS_EVENT__HPP