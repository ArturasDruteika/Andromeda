#ifndef WINDOW__EVENT_DISPATCHER__HPP
#define WINDOW__EVENT_DISPATCHER__HPP


#include "Andromeda/Window/Events/IEvent.hpp"


namespace Andromeda::Window
{
	class EventDispatcher
	{
	public:
		EventDispatcher(IEvent& event);
		~EventDispatcher();

        // F will be deduced by the compiler
        // F: bool(T&)
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            // Prefer dynamic_cast so we don't need GetStaticType / macros
            if (auto* e = dynamic_cast<T*>(&m_event))
            {
                bool handled = func(*e);
                if (handled)
                {
                    m_event.SetHandled(true);
                }
                return handled;
            }
            return false;
        }

	private:
		IEvent& m_event;
	};
}


#endif // WINDOW__EVENT_DISPATCHER__HPP