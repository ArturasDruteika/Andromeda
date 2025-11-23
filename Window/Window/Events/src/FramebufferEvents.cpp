#include "../include/FramebufferEvents.hpp"
#include <sstream>


namespace Andromeda::Window
{
    // WindowResizeEvent

    WindowResizeEvent::WindowResizeEvent(int width, int height)
        : m_width{ width }
        , m_height{ height }
    {
    }

    WindowResizeEvent::~WindowResizeEvent() = default;

    int WindowResizeEvent::GetWidth() const
    {
        return m_width;
    }

    int WindowResizeEvent::GetHeight() const
    {
        return m_height;
    }

    bool WindowResizeEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int WindowResizeEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryApplication;
    }

    std::string WindowResizeEvent::GetName() const
    {
        return "WindowResize";
    }

    std::string WindowResizeEvent::ToString() const
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

    Andromeda::EventType WindowResizeEvent::GetEventType() const
    {
        return Andromeda::EventType::WindowResize;
    }

    // WindowCloseEvent

    WindowCloseEvent::WindowCloseEvent() = default;

    WindowCloseEvent::~WindowCloseEvent() = default;

    bool WindowCloseEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int WindowCloseEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryApplication;
    }

    std::string WindowCloseEvent::GetName() const
    {
        return "WindowClose";
    }

    std::string WindowCloseEvent::ToString() const
    {
        return "WindowCloseEvent";
    }

    Andromeda::EventType WindowCloseEvent::GetEventType() const
    {
        return Andromeda::EventType::WindowClose;
    }

    // FramebufferResizeEvent

    FramebufferResizeEvent::FramebufferResizeEvent(int width, int height)
        : m_width{ width }
        , m_height{ height }
    {
    }

    FramebufferResizeEvent::~FramebufferResizeEvent() = default;

    int FramebufferResizeEvent::GetWidth() const
    {
        return m_width;
    }

    int FramebufferResizeEvent::GetHeight() const
    {
        return m_height;
    }

    bool FramebufferResizeEvent::IsInCategory(Andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int FramebufferResizeEvent::GetCategoryFlags() const
    {
        return Andromeda::EventCategoryApplication;
    }

    std::string FramebufferResizeEvent::GetName() const
    {
        return "FramebufferResize";
    }

    std::string FramebufferResizeEvent::ToString() const
    {
        std::stringstream ss;
        ss << "FramebufferResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

    EventType FramebufferResizeEvent::GetEventType() const
    {
        return EventType::WindowResize;
    }
}
