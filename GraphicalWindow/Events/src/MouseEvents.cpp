#include "../include/MouseEvents.hpp"
#include "../include/EventType.hpp"


namespace Andromeda
{
	namespace GraphicalWindow 
	{
		MouseMovedEvent::MouseMovedEvent(const float x, const float y)
			: m_x{ x }
			, m_y{ y }
		{
		}

		float MouseMovedEvent::GetX() const
		{
			return m_x;
		}

		float MouseMovedEvent::GetY() const
		{
			return m_y;
		}

		std::string MouseMovedEvent::ToString() const
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_x << ", " << m_y;
			return ss.str();
		}

		MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_xOffset{ xOffset }
			, m_yOffset{ yOffset }
		{
		}

		float MouseScrolledEvent::GetXOffset() const
		{
			return m_xOffset;
		}

		float MouseScrolledEvent::GetYOffset() const
		{
			return m_yOffset;
		}

		std::string MouseScrolledEvent::ToString() const
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		MouseCode MouseButtonEvent::GetMouseButton() const
		{
			return m_button;
		}

		MouseButtonEvent::MouseButtonEvent(const MouseCode button)
			: m_button{ button }
		{
		}

		MouseButtonPressedEvent::MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent{ button }
		{
		}

		std::string MouseButtonPressedEvent::ToString() const
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent{ button }
		{
		}

		std::string MouseButtonReleasedEvent::ToString() const
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
	}
}