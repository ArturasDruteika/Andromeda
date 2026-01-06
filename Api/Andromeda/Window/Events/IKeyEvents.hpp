#ifndef API__WINDOW__EVENTS__I_KEY_EVENTS_HPP
#define API__WINDOW__EVENTS__I_KEY_EVENTS_HPP


#include "IEvent.hpp"
#include "../MouseAndKeyCodes/KeyCodes.hpp"


namespace Andromeda
{
    // Base interface for all key-related events
    class IKeyEvent
        : public virtual IEvent
    {
    public:
        virtual ~IKeyEvent() = default;
        virtual KeyCode GetKeyCode() const = 0;
    };

    // Key pressed (may repeat)
    class IKeyPressedEvent
        : public virtual IKeyEvent
    {
    public:
        virtual ~IKeyPressedEvent() = default;
        virtual bool IsRepeat() const = 0;
    };

    // Key released
    class IKeyReleasedEvent
        : public virtual IKeyEvent
    {
    public:
        virtual ~IKeyReleasedEvent() = default;
    };

    // Key typed (character input)
    class IKeyTypedEvent
        : public virtual IKeyEvent
    {
    public:
        virtual ~IKeyTypedEvent() = default;
    };
}

#endif // API__WINDOW__EVENTS__I_KEY_EVENTS_HPP
