#ifndef ANDROMEDA__WINDOW__EVENT__HPP
#define ANDROMEDA__WINDOW__EVENT__HPP


#include "EventType.hpp"
#include <string>


namespace Andromeda
{
	class IEvent
	{
	public:
		virtual ~IEvent() = default;

		virtual bool IsInCategory(EventCategory category) = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string GetName() const = 0;
		virtual std::string ToString() const = 0;
		virtual EventType GetEventType() const = 0;
	};
}


#endif // ANDROMEDA__WINDOW__EVENT__HPP