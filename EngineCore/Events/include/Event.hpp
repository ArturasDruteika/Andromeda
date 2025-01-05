#ifndef ENGINE_CORE__EVENT__HPP
#define ENGINE_CORE__EVENT__HPP


#include "EventType.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class Event
		{
		public:
			Event();
			~Event();

			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual int GetCategoryFlags() const = 0;
			virtual std::string ToString() const;
			bool IsInCategory(EventCategory category);

			bool Handled = false;
		};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


		inline std::ostream& operator<<(std::ostream& os, const Event& e)
		{
			return os << e.ToString();
		}

	}
}


#endif // ENGINE_CORE__EVENT__HPP