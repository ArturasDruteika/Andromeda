#ifndef GRAPHICAL_WINDOW__FRAME_BUFFER_RESIZE_EVENT__HPP
#define GRAPHICAL_WINDOW__FRAME_BUFFER_RESIZE_EVENT__HPP


#include "EventType.hpp"
#include "Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class FramebufferResizeEvent : public Event
		{
		public:
			FramebufferResizeEvent();
			~FramebufferResizeEvent();

		protected:
		};
	}
}


#endif // GRAPHICAL_WINDOW__FRAME_BUFFER_RESIZE_EVENT__HPP