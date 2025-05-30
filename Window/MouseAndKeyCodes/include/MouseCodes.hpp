#ifndef WINDOW__MOUSE_CODES__HPP
#define WINDOW__MOUSE_CODES__HPP


#include "pch.hpp"


namespace Andromeda
{
	using MouseCode = uint16_t;

	namespace Window
	{
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}


#endif // WINDOW__MOUSE_CODES__HPP