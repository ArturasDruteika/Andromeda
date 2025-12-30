#ifndef WINDOW__KEY_EVENTS__HPP
#define WINDOW__KEY_EVENTS__HPP


#include "EventBase.hpp"
#include "Andromeda/Window/Events/EventType.hpp"
#include "Andromeda/Window/MouseAndKeyCodes/KeyCodes.hpp"
#include "Andromeda/Window/Events/IKeyEvents.hpp"
#include "pch.hpp"


namespace Andromeda::Window
{
    class KeyEvent
        : public EventBase
        , public virtual IKeyEvent
    {
    public:
        explicit KeyEvent(KeyCode keycode);
        ~KeyEvent() override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;

        KeyCode GetKeyCode() const override;

    protected:
        KeyCode m_keyCode;
    };

    class KeyPressedEvent
        : public KeyEvent
        , public virtual IKeyPressedEvent
    {
    public:
        KeyPressedEvent(KeyCode keycode, bool isRepeat);
        ~KeyPressedEvent() override;

        bool IsRepeat() const override;

        EventType GetEventType() const override;
        std::string GetName() const override;
        std::string ToString() const override;

    private:
        bool m_isRepeat;
    };

    class KeyReleasedEvent
        : public KeyEvent
        , public virtual IKeyReleasedEvent
    {
    public:
        explicit KeyReleasedEvent(KeyCode keycode);
        ~KeyReleasedEvent() override;

        EventType GetEventType() const override;
        std::string GetName() const override;
        std::string ToString() const override;
    };

    class KeyTypedEvent
        : public KeyEvent
        , public virtual IKeyTypedEvent
    {
    public:
        explicit KeyTypedEvent(KeyCode keycode);
        ~KeyTypedEvent() override;

        EventType GetEventType() const override;
        std::string GetName() const override;
        std::string ToString() const override;
    };
}

#endif // WINDOW__KEY_EVENTS__HPP
