#ifndef WINDOW__EVENTS_TYPE__HPP
#define WINDOW__EVENTS_TYPE__HPP


#include <string>


namespace Andromeda
{
	namespace GraphicalWindow
	{
		struct EventType
		{
			inline static const std::string CURSOR_MOVE = "Cursor Move";
			inline static const std::string KEYBOARD_PRESS = "Keyboard Press";
			inline static const std::string RESIZE_WINDOW = "ResizeWindow";
		};
	}
}


#endif // WINDOW__EVENTS_TYPE__HPP