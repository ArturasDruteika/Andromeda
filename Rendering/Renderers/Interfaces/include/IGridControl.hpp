#ifndef RENDERER__I_GRID_CONTROL__HPP
#define RENDERER__I_GRID_CONTROL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IGridControl
	{
	public:
		virtual ~IGridControl();

		// Getters
		virtual bool IsGridVisible() const = 0;
		// Setters
		virtual void SetGridVisible(bool visible) = 0;
	};
}


#endif // RENDERER__I_GRID_CONTROL__HPP