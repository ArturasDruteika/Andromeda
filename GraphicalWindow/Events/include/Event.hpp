#ifndef WINDOW__EVENT__HPP
#define WINDOW__EVENT__HPP


#include "EventType.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class Event
		{
		public:
			Event();
			~Event();

			std::string GetEventType() const;

		protected:
			std::string m_eventType;
		};
	}
}


#endif // WINDOW__EVENT__HPP