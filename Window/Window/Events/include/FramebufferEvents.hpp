#ifndef WINDOW__FRAMEBUFFER_EVENTS__HPP
#define WINDOW__FRAMEBUFFER_EVENTS__HPP


#include "Andromeda/Window/EventType.hpp"
#include "Andromeda/Window/IEvent.hpp"
#include <string>


namespace Andromeda::Window
{
    class WindowResizeEvent
        : public IEvent
    {
    public:
        WindowResizeEvent(int width, int height);
        ~WindowResizeEvent() override;

        int GetWidth() const;
        int GetHeight() const;

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
        : public IEvent
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
        : public IEvent
    {
    public:
        FramebufferResizeEvent(int width, int height);
        ~FramebufferResizeEvent() override;

        int GetWidth() const;
        int GetHeight() const;

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
