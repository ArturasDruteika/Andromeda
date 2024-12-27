#ifndef WINDOW__EVENTS__HPP
#define WINDOW__EVENTS__HPP


#include "EventType.hpp"


namespace Andromeda
{
	namespace Window
	{
		class Event
		{
		public:
			Event();
			~Event();

			EventType GetEventType() const;

		protected:
			EventType m_eventType;
		};
	}
}


#endif // WINDOW__EVENTS__HPP