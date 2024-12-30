#ifndef GRAPHICAL_WINDOW__KEY_EVENTS__HPP
#define GRAPHICAL_WINDOW__KEY_EVENTS__HPP


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


#include "EventType.hpp"
#include "Event.hpp"
#include "../../MouseAndKeyCodes/include/KeyCodes.hpp"

namespace Andromeda
{
	namespace GraphicalWindow
	{
		class GRAPHICALWINDOW_API KeyEvent : public Event
		{
		public:
			KeyCode GetKeyCode() const;

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

		protected:
			KeyEvent(const KeyCode keycode);

			KeyCode m_keyCode;
		};

		class GRAPHICALWINDOW_API KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(const KeyCode keycode, bool isRepeat = false);

			bool IsRepeat() const;
			std::string ToString() const override;

			EVENT_CLASS_TYPE(KeyPressed)

		private:
			bool m_isRepeat;
		};

		class GRAPHICALWINDOW_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(const KeyCode keycode);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(KeyReleased)
		};

		class GRAPHICALWINDOW_API KeyTypedEvent : public KeyEvent
		{
		public:
			KeyTypedEvent(const KeyCode keycode);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(KeyTyped)
		};
	}
}


#endif // GRAPHICAL_WINDOW__KEY_EVENTS__HPP