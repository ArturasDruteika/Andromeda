#ifndef WINDOW__EVENT_BASE__HPP
#define WINDOW__EVENT_BASE__HPP


#include "Andromeda/Window/IEvent.hpp"


namespace Andromeda::Window
{
    class EventBase
        : public IEvent
    {
    public:
        EventBase();
        ~EventBase() override;

        bool IsHandled() const override;
        void SetHandled(bool handled) override;

    private:
        bool m_handled;
    };
}


#endif // WINDOW__EVENT_BASE__HPP