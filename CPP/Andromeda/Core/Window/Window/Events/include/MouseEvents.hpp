#ifndef WINDOW__MOUSE_EVENTS__HPP
#define WINDOW__MOUSE_EVENTS__HPP


#include "EventBase.hpp"
#include "Andromeda/Window/Events/EventType.hpp"
#include "Andromeda/Window/MouseAndKeyCodes/MouseCodes.hpp"
#include "Andromeda/Window/Events/IMouseEvents.hpp"
#include "pch.hpp"


namespace Andromeda::Window
{
    class MouseMovedEvent
        : public EventBase
        , public virtual IMouseMovedEvent
    {
    public:
        MouseMovedEvent(float x, float y);
        ~MouseMovedEvent() override = default;

        float GetX() const override;
        float GetY() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;

    private:
        float m_x;
        float m_y;
    };

    class MouseScrolledEvent
        : public EventBase
        , public virtual IMouseScrolledEvent
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset);
        ~MouseScrolledEvent() override = default;

        float GetXOffset() const override;
        float GetYOffset() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;

    private:
        float m_xOffset;
        float m_yOffset;
    };

    class MouseButtonEvent
        : public EventBase
        , public virtual IMouseButtonEvent
    {
    public:
        explicit MouseButtonEvent(MouseCode button);
        ~MouseButtonEvent() override = default;

        MouseCode GetMouseButton() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;

    protected:
        MouseCode m_button;
    };

    class MouseButtonPressedEvent
        : public MouseButtonEvent
        , public virtual IMouseButtonPressedEvent
    {
    public:
        explicit MouseButtonPressedEvent(MouseCode button);
        ~MouseButtonPressedEvent() override = default;

        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;
    };

    class MouseButtonReleasedEvent
        : public MouseButtonEvent
        , public virtual IMouseButtonReleasedEvent
    {
    public:
        explicit MouseButtonReleasedEvent(MouseCode button);
        ~MouseButtonReleasedEvent() override = default;

        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;
    };
}

#endif // WINDOW__MOUSE_EVENTS__HPP
