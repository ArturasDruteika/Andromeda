#include "../include/MouseEvents.hpp"
#include <sstream>


namespace Andromeda::Window
{
    // MouseMovedEvent

    MouseMovedEvent::MouseMovedEvent(float x, float y)
        : m_x{ x }
        , m_y{ y }
    {
    }

    float MouseMovedEvent::GetX() const
    {
        return m_x;
    }

    float MouseMovedEvent::GetY() const
    {
        return m_y;
    }

    bool MouseMovedEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int MouseMovedEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryMouse |
            Andromeda::EventCategoryInput;
    }

    std::string MouseMovedEvent::GetName() const
    {
        return "MouseMoved";
    }

    std::string MouseMovedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_x << ", " << m_y;
        return ss.str();
    }

    Andromeda::EventType MouseMovedEvent::GetEventType() const
    {
        return Andromeda::EventType::MouseMoved;
    }

    // MouseScrolledEvent

    MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset)
        : m_xOffset{ xOffset }
        , m_yOffset{ yOffset }
    {
    }

    float MouseScrolledEvent::GetXOffset() const
    {
        return m_xOffset;
    }

    float MouseScrolledEvent::GetYOffset() const
    {
        return m_yOffset;
    }

    bool MouseScrolledEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int MouseScrolledEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryMouse |
            Andromeda::EventCategoryInput;
    }

    std::string MouseScrolledEvent::GetName() const
    {
        return "MouseScrolled";
    }

    std::string MouseScrolledEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
        return ss.str();
    }

    Andromeda::EventType MouseScrolledEvent::GetEventType() const
    {
        return Andromeda::EventType::MouseScrolled;
    }

    // MouseButtonEvent

    MouseButtonEvent::MouseButtonEvent(Andromeda::MouseCode button)
        : m_button{ button }
    {
    }

    Andromeda::MouseCode MouseButtonEvent::GetMouseButton() const
    {
        return m_button;
    }

    bool MouseButtonEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int MouseButtonEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryMouse |
            Andromeda::EventCategoryInput |
            Andromeda::EventCategoryMouseButton;
    }

    // MouseButtonPressedEvent

    MouseButtonPressedEvent::MouseButtonPressedEvent(Andromeda::MouseCode button)
        : MouseButtonEvent{ button }
    {
    }

    std::string MouseButtonPressedEvent::GetName() const
    {
        return "MouseButtonPressed";
    }

    std::string MouseButtonPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << static_cast<int>(m_button);
        return ss.str();
    }

    Andromeda::EventType MouseButtonPressedEvent::GetEventType() const
    {
        return Andromeda::EventType::MouseButtonPressed;
    }

    // MouseButtonReleasedEvent

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(Andromeda::MouseCode button)
        : MouseButtonEvent{ button }
    {
    }

    std::string MouseButtonReleasedEvent::GetName() const
    {
        return "MouseButtonReleased";
    }

    std::string MouseButtonReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_button);
        return ss.str();
    }

    Andromeda::EventType MouseButtonReleasedEvent::GetEventType() const
    {
        return Andromeda::EventType::MouseButtonReleased;
    }
}
