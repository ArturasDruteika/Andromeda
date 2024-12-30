#ifndef GRAPHICAL_WINDOW__MOUSE_EVENTS__HPP
#define GRAPHICAL_WINDOW__MOUSE_EVENTS__HPP


#if defined(_WIN32)
	#if defined(GRAPHICALWINDOW_EXPORT)
		#define GRAPHICALWINDOW_API __declspec(dllexport)
	#else
		#define GRAPHICALWINDOW_API __declspec(dllimport)
	#endif /* GRAPHICALWINDOW_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define GRAPHICALWINDOW_API __attribute__((visibility("default")))
#endif


#include "Event.hpp"
#include "EventType.hpp"
#include "../../MouseAndKeyCodes/include/MouseCodes.hpp"
#include <sstream>


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class GRAPHICALWINDOW_API MouseMovedEvent : public Event
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

		class GRAPHICALWINDOW_API MouseScrolledEvent : public Event
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

		class GRAPHICALWINDOW_API MouseButtonEvent : public Event
		{
		public:
			MouseCode GetMouseButton() const;

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
		protected:
			MouseButtonEvent(const MouseCode button);

			MouseCode m_button;
		};

		class GRAPHICALWINDOW_API MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(const MouseCode button);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};
		
		class GRAPHICALWINDOW_API MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(const MouseCode button);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};
	}
}


#endif // GRAPHICAL_WINDOW__MOUSE_EVENTS__HPP