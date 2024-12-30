#ifndef GRAPHICAL_WINDOW__FRAME_BUFFER_EVENTS__HPP
#define GRAPHICAL_WINDOW__FRAME_BUFFER_EVENTS__HPP


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
#include "Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class GRAPHICALWINDOW_API WindowResizeEvent : public Event
		{
		public:
			WindowResizeEvent(unsigned int width, unsigned int height);

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string ToString() const override;

			EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

		private:
			unsigned int m_width, m_height;
		};

		class WindowCloseEvent : public Event
		{
		public:
			WindowCloseEvent() = default;

			EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class AppTickEvent : public Event
		{
		public:
			AppTickEvent() = default;

			EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class AppUpdateEvent : public Event
		{
		public:
			AppUpdateEvent() = default;

			EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class AppRenderEvent : public Event
		{
		public:
			AppRenderEvent() = default;

			EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};
	}
}


#endif // GRAPHICAL_WINDOW__FRAME_BUFFER_EVENTS__HPP