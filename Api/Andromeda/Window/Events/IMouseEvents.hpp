#ifndef API__WINDOW__EVENTS__I_MOUSE_EVENTS_HPP
#define API__WINDOW__EVENTS__I_MOUSE_EVENTS_HPP


#include "IEvent.hpp"
#include "../MouseAndKeyCodes/MouseCodes.hpp"


namespace Andromeda
{
    class IMouseMovedEvent
        : public virtual IEvent
    {
    public:
        virtual ~IMouseMovedEvent() = default;
        virtual float GetX() const = 0;
        virtual float GetY() const = 0;
    };

    class IMouseScrolledEvent
        : public virtual IEvent
    {
    public:
        virtual ~IMouseScrolledEvent() = default;

        // You already use Y in engine for zoom; keep this.
        virtual float GetYOffset() const = 0;

        // Optional but useful for completeness; you already store it in Window.
        virtual float GetXOffset() const = 0;
    };

    class IMouseButtonEvent
        : public virtual IEvent
    {
    public:
        virtual ~IMouseButtonEvent() = default;
        virtual MouseCode GetMouseButton() const = 0;
    };

    class IMouseButtonPressedEvent
        : public virtual IMouseButtonEvent
    {
    public:
        virtual ~IMouseButtonPressedEvent() = default;
    };

    class IMouseButtonReleasedEvent
        : public virtual IMouseButtonEvent
    {
    public:
        virtual ~IMouseButtonReleasedEvent() = default;
    };
}

#endif // API__WINDOW__EVENTS__I_MOUSE_EVENTS_HPP
