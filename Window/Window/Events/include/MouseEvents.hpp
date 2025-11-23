#ifndef WINDOW__MOUSE_EVENTS__HPP
#define WINDOW__MOUSE_EVENTS__HPP


#include "Andromeda/Window/EventType.hpp"
#include "Andromeda/Window/IEvent.hpp"
#include "../../MouseAndKeyCodes/include/MouseCodes.hpp"


namespace Andromeda::Window
{
    class MouseMovedEvent
        : public IEvent
    {
    public:
        MouseMovedEvent(float x, float y);
        ~MouseMovedEvent() override = default;

        float GetX() const;
        float GetY() const;

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
        : public IEvent
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset);
        ~MouseScrolledEvent() override = default;

        float GetXOffset() const;
        float GetYOffset() const;

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
        : public IEvent
    {
    public:
        explicit MouseButtonEvent(MouseCode button);
        virtual ~MouseButtonEvent() override = default;

        MouseCode GetMouseButton() const;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;

    protected:
        MouseCode m_button;
    };

    class MouseButtonPressedEvent
        : public MouseButtonEvent
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
