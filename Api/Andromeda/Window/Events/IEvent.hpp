#ifndef API__WINDOW__EVENTS__I_EVENT_HPP
#define API__WINDOW__EVENTS__I_EVENT_HPP


#include "EventType.hpp"
#include <string>


namespace Andromeda
{
	class IEvent
	{
	public:
		virtual ~IEvent() = default;

		virtual bool IsHandled() const = 0;
		virtual void SetHandled(bool handled) = 0;
		virtual bool IsInCategory(EventCategory category) = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string GetName() const = 0;
		virtual std::string ToString() const = 0;
		virtual EventType GetEventType() const = 0;
	};
}


#endif // API__WINDOW__EVENTS__I_EVENT_HPP