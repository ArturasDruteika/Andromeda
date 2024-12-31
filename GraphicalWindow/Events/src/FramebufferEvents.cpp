#include "../include/FramebufferEvents.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width)
			, m_height(height)
		{
		}

		unsigned int WindowResizeEvent::GetWidth() const
		{
			return m_width;
		}

		unsigned int WindowResizeEvent::GetHeight() const
		{
			return m_height;
		}

		std::string WindowResizeEvent::ToString() const
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}
	}
}