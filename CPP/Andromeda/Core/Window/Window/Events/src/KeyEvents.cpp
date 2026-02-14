#include "../include/KeyEvents.hpp"
#include <sstream>


namespace Andromeda::Window
{
    // KeyEvent

    KeyEvent::~KeyEvent() = default;

    KeyEvent::KeyEvent(Andromeda::KeyCode keycode)
        : m_keyCode{ keycode }
    {
    }

    Andromeda::KeyCode KeyEvent::GetKeyCode() const
    {
        return m_keyCode;
    }

    bool KeyEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int KeyEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryKeyboard |
            Andromeda::EventCategoryInput;
    }

    // KeyPressedEvent

    KeyPressedEvent::KeyPressedEvent(Andromeda::KeyCode keycode, bool isRepeat)
        : KeyEvent{ keycode }
        , m_isRepeat{ isRepeat }
    {
    }

    KeyPressedEvent::~KeyPressedEvent() = default;

    bool KeyPressedEvent::IsRepeat() const
    {
        return m_isRepeat;
    }

    Andromeda::EventType KeyPressedEvent::GetEventType() const
    {
        return Andromeda::EventType::KeyPressed;
    }

    std::string KeyPressedEvent::GetName() const
    {
        return "KeyPressed";
    }

    std::string KeyPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << static_cast<int>(m_keyCode)
            << " repeat=" << (m_isRepeat ? "true" : "false");
        return ss.str();
    }

    // KeyReleasedEvent

    KeyReleasedEvent::KeyReleasedEvent(Andromeda::KeyCode keycode)
        : KeyEvent{ keycode }
    {
    }

    KeyReleasedEvent::~KeyReleasedEvent() = default;

    Andromeda::EventType KeyReleasedEvent::GetEventType() const
    {
        return Andromeda::EventType::KeyReleased;
    }

    std::string KeyReleasedEvent::GetName() const
    {
        return "KeyReleased";
    }

    std::string KeyReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << static_cast<int>(m_keyCode);
        return ss.str();
    }

    // KeyTypedEvent

    KeyTypedEvent::KeyTypedEvent(Andromeda::KeyCode keycode)
        : KeyEvent{ keycode }
    {
    }

    KeyTypedEvent::~KeyTypedEvent() = default;

    Andromeda::EventType KeyTypedEvent::GetEventType() const
    {
        return Andromeda::EventType::KeyTyped;
    }

    std::string KeyTypedEvent::GetName() const
    {
        return "KeyTyped";
    }

    std::string KeyTypedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << static_cast<int>(m_keyCode);
        return ss.str();
    }
}
