#ifndef API__WINDOW__EVENTS__I_FRAMEBUFFER_EVENTS_HPP
#define API__WINDOW__EVENTS__I_FRAMEBUFFER_EVENTS_HPP


#include "IEvent.hpp"


namespace Andromeda
{
    class IWindowResizeEvent
        : public virtual IEvent
    {
    public:
        virtual ~IWindowResizeEvent() = default;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
    };

    class IWindowCloseEvent
        : public virtual IEvent
    {
    public:
        virtual ~IWindowCloseEvent() = default;
    };

    class IFramebufferResizeEvent
        : public virtual IEvent
    {
    public:
        virtual ~IFramebufferResizeEvent() = default;
        
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
    };
}

#endif // API__WINDOW__EVENTS__I_FRAMEBUFFER_EVENTS_HPP
