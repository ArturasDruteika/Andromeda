#include "../include/FramebufferEvents.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		FramebufferResizeEvent::FramebufferResizeEvent()
			: m_width(0)
			, m_height(0)
		{
		}

		FramebufferResizeEvent::~FramebufferResizeEvent()
		{
		}

		int FramebufferResizeEvent::GetWidth() const
		{
			return m_width;
		}

		int FramebufferResizeEvent::GetHeight() const
		{
			return m_height;
		}
	}
}