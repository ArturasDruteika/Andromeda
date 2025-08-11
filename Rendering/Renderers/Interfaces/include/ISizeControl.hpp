#ifndef RENDERER__I_SIZE__HPP
#define RENDERER__I_SIZE__HPP


#include "../../../MacroExports/include/MacroExports.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ISizeControl
	{
	public:
		virtual ~ISizeControl();

		// Getters
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void Resize(int width, int height) = 0;
	};
}


#endif // RENDERER__I_SIZE__HPP