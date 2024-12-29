#include "../include/MouseEvents.hpp"
#include "../include/EventType.hpp"


namespace Andromeda
{
	namespace GraphicalWindow 
	{
		MouseMoveEvent::MouseMoveEvent()
			: m_x(0.0)
			, m_y(0.0)
		{
		}

		MouseMoveEvent::~MouseMoveEvent()
		{
		}

		double MouseMoveEvent::GetX() const
		{
			return m_x;
		}

		double MouseMoveEvent::GetY() const
		{
			return m_y;
		}
	}
}