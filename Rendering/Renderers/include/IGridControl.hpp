#ifndef RENDERER__I_GRID_CONTROL__HPP
#define RENDERER__I_GRID_CONTROL__HPP


namespace Andromeda::Rendering
{
	class IGridControl
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