#ifndef WINDOW__FRAME_BUFFER_EVENTS__HPP
#define WINDOW__FRAME_BUFFER_EVENTS__HPP


#include "EventType.hpp"
#include "Event.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class WindowResizeEvent : public Event
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


#endif // WINDOW__FRAME_BUFFER_EVENTS__HPP