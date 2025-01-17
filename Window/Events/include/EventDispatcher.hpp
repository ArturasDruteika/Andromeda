#ifndef WINDOW__EVENT_DISPATCHER__HPP
#define WINDOW__EVENT_DISPATCHER__HPP


#include "Event.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class EventDispatcher
		{
		public:
			EventDispatcher(Event& event);

			// F will be deduced by the compiler
			template<typename T, typename F>
			bool Dispatch(const F& func)
			{
				if (m_event.GetEventType() == T::GetStaticType())
				{
					m_event.Handled |= func(static_cast<T&>(m_event));
					return true;
				}
				return false;
			}

		private:
			Event& m_event;
		};
	}
}


#endif // WINDOW__EVENT_DISPATCHER__HPP