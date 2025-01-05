#ifndef ENGINECORE__KEY_EVENTS__HPP
#define ENGINECORE__KEY_EVENTS__HPP


#include "EventType.hpp"
#include "Event.hpp"
#include "../../MouseAndKeyCodes/include/KeyCodes.hpp"

namespace Andromeda
{
	namespace EngineCore
	{
		class KeyEvent : public Event
		{
		public:
			KeyCode GetKeyCode() const;

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

		protected:
			KeyEvent(const KeyCode keycode);

			KeyCode m_keyCode;
		};

		class KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(const KeyCode keycode, bool isRepeat = false);

			bool IsRepeat() const;
			std::string ToString() const override;

			EVENT_CLASS_TYPE(KeyPressed)

		private:
			bool m_isRepeat;
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(const KeyCode keycode);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(KeyReleased)
		};

		class KeyTypedEvent : public KeyEvent
		{
		public:
			KeyTypedEvent(const KeyCode keycode);

			std::string ToString() const override;

			EVENT_CLASS_TYPE(KeyTyped)
		};
	}
}


#endif // ENGINECORE__KEY_EVENTS__HPP