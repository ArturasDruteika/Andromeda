#ifndef WINDOW__EVENT_DISPATCHER__HPP
#define WINDOW__EVENT_DISPATCHER__HPP


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

#include "Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class GRAPHICALWINDOW_API EventDispatcher
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