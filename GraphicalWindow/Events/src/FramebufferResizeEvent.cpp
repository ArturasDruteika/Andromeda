#include "FramebufferResizeEvent.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		FramebufferResizeEvent::FramebufferResizeEvent()
		{
			m_eventType = EventType::RESIZE_WINDOW;
		}

		FramebufferResizeEvent::~FramebufferResizeEvent()
		{
		}
	}
}