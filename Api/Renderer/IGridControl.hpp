#ifndef API_RENDERER__I_GRID_CONTROL__HPP
#define API_RENDERER__I_GRID_CONTROL__HPP


namespace Andromeda
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


#endif // API_RENDERER__I_GRID_CONTROL__HPP