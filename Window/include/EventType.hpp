#ifndef WINDOW__EVENTS_TYPE__HPP
#define WINDOW__EVENTS_TYPE__HPP


#include <string>


namespace Andromeda
{
	namespace Window
	{
		struct EventType
		{
			inline static const std::string MOUSE = "Mouse";
			inline static const std::string KEYBOARD = "Keyboard";
			inline static const std::string RESIZE = "Resize";
		};
	}
}


#endif // WINDOW__EVENTS_TYPE__HPP