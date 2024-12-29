#ifndef GRAPHICAL_WINDOW__FRAME_BUFFER_RESIZE_EVENT__HPP
#define GRAPHICAL_WINDOW__FRAME_BUFFER_RESIZE_EVENT__HPP


#include "EventType.hpp"
#include "Event.hpp"
#include <GLFW/glfw3.h>


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class FramebufferResizeEvent : public Event
		{
		public:
			FramebufferResizeEvent();
			~FramebufferResizeEvent();

			int GetWidth() const;
			int GetHeight() const;

		private:
			int m_width;
			int m_height;
		};
	}
}


#endif // GRAPHICAL_WINDOW__FRAME_BUFFER_RESIZE_EVENT__HPP