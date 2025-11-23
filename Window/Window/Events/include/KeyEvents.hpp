#ifndef WINDOW__KEY_EVENTS__HPP
#define WINDOW__KEY_EVENTS__HPP


#include "EventBase.hpp"
#include "../../MouseAndKeyCodes/include/KeyCodes.hpp"
#include "Andromeda/Window/EventType.hpp"
#include <string>


namespace Andromeda::Window
{
    class KeyEvent
        : public EventBase
    {
    public:
        explicit KeyEvent(KeyCode keycode);
        virtual ~KeyEvent() override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;

        KeyCode GetKeyCode() const;

    protected:
        KeyCode m_keyCode;
    };

    class KeyPressedEvent
        : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keycode, bool isRepeat);
        ~KeyPressedEvent() override;

        bool IsRepeat() const;

        EventType GetEventType() const override;
        std::string GetName() const override;
        std::string ToString() const override;

    private:
        bool m_isRepeat;
    };

    class KeyReleasedEvent
        : public KeyEvent
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
