#ifndef API__WINDOW__EVENTS__EVENTS_TYPE__HPP
#define API__WINDOW__EVENTS__EVENTS_TYPE__HPP


namespace Andromeda
{
#define BIT(x) (1 << x)


	enum class EventType
	{
		None = 0,
		WindowClose, 
		WindowResize, 
		WindowFocus, 
		WindowLostFocus, 
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed, 
		MouseButtonReleased, 
		MouseMoved, 
		MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
}


#endif // API__WINDOW__EVENTS__EVENTS_TYPE__HPP