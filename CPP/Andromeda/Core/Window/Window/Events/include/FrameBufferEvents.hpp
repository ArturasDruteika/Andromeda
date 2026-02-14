#ifndef WINDOW__FRAMEBUFFER_EVENTS__HPP
#define WINDOW__FRAMEBUFFER_EVENTS__HPP


#include "EventBase.hpp"
#include "Andromeda/Window/Events/EventType.hpp"
#include "Andromeda/Window/Events/IFrameBufferEvents.hpp"

#include <string>


namespace Andromeda::Window
{
    class WindowResizeEvent
        : public EventBase
        , public virtual Andromeda::IWindowResizeEvent
    {
    public:
        WindowResizeEvent(int width, int height);
        ~WindowResizeEvent() override;

        int GetWidth() const override;
        int GetHeight() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;

    private:
        int m_width;
        int m_height;
    };

    class WindowCloseEvent
        : public EventBase
        , public virtual Andromeda::IWindowCloseEvent
    {
    public:
        WindowCloseEvent();
        ~WindowCloseEvent() override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;
    };

    class FramebufferResizeEvent
        : public EventBase
        , public virtual Andromeda::IFramebufferResizeEvent
    {
    public:
        FramebufferResizeEvent(int width, int height);
        ~FramebufferResizeEvent() override;

        int GetWidth() const override;
        int GetHeight() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;

    private:
        int m_width;
        int m_height;
    };
}

#endif // WINDOW__FRAMEBUFFER_EVENTS__HPP
