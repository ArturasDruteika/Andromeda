#include "../include/KeyEvents.hpp"
#include <sstream>


namespace Andromeda
{
	namespace Window
	{
		KeyCode KeyEvent::GetKeyCode() const
		{
			return m_keyCode;
		}
		KeyEvent::KeyEvent(const KeyCode keycode)
			: m_keyCode{ keycode }
		{
		}

		KeyPressedEvent::KeyPressedEvent(const KeyCode keycode, bool isRepeat)
			: KeyEvent{ keycode }
			, m_isRepeat{ isRepeat }
		{
		}

		bool KeyPressedEvent::IsRepeat() const
		{
			return m_isRepeat;
		}

		std::string KeyPressedEvent::ToString() const
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (repeat = " << m_isRepeat << ")";
			return ss.str();
		}

		KeyReleasedEvent::KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent{ keycode }
		{
		}

		std::string KeyReleasedEvent::ToString() const
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		KeyTypedEvent::KeyTypedEvent(const KeyCode keycode)
			: KeyEvent{ keycode }
		{
		}

		std::string KeyTypedEvent::ToString() const
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keyCode;
			return ss.str();
		}
	}
}