#ifndef WINDOW__MOUSE_EVENTS__HPP
#define WINDOW__MOUSE_EVENTS__HPP


#include "EventType.hpp"
#include "Event.hpp"
#include "../../MouseAndKeyCodes/include/MouseCodes.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class MouseMovedEvent : public Event
		{
		public:
			MouseMovedEvent(const float x, const float y);

			float GetX() const;
			float GetY() const;
			std::string ToString() const override;

			EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		private:
			float m_x, m_y;
		};

		class MouseScrolledEvent : public Event
		{
		public:
			MouseScrolledEvent(const float xOffset, const float yOffset);

			float GetXOffset() const;
			float GetYOffset() const;

			std::string ToString() const override;

			EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float m_xOffset, m_yOffset;
		};

		class MouseButtonEvent : public Event
		{
		public:
			MouseCode GetMouseButton() const;

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
		protected:
			MouseButtonEvent(const MouseCode button);

			MouseCode m_button;
		};

		class MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(const MouseCode button);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};
		
		class MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(const MouseCode button);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};
	}
}


#endif // WINDOW__MOUSE_EVENTS__HPP