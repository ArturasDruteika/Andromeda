#ifndef WINDOW__EVENT__HPP
#define WINDOW__EVENT__HPP


#if defined(_WIN32)
	#if defined(GRAPHICALWINDOW_EXPORT)
		#define GRAPHICALWINDOW_API __declspec(dllexport)
	#else
		#define GRAPHICALWINDOW_API __declspec(dllimport)
	#endif /* GRAPHICALWINDOW_API */
	#define _sprintf sprintf_s
	#endif

#if defined(__GNUC__)
	// GCC
	#define GRAPHICALWINDOW_API __attribute__((visibility("default")))
#endif


#include "EventType.hpp"
#include <sstream>


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class GRAPHICALWINDOW_API Event
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


#endif // WINDOW__EVENT__HPP