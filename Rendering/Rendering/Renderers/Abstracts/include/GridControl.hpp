#ifndef RENDERER__GRID_CONTROL__HPP
#define RENDERER__GRID_CONTROL__HPP


#include "Andromeda/Space/Colors//Colors.hpp"


namespace Andromeda::Rendering
{
	class GridControl
	{
	public:
		GridControl();
		~GridControl();

		// Getters
		bool IsGridVisible() const;
		float GetGridSize() const;
		float GetGridSpacing() const;
		float GetGridLineWidth() const;
		const Color& GetGridColor() const;
		// Setters
		void SetGridVisible(bool visible);
		void SetGridSize(float size);
		void SetGridSpacing(float spacing);
		void SetGridLineWidth(float lineWidth);
		void SetGridColor(const Color& color);


	protected:
		bool m_isGridVisible; // Flag to control grid visibility
		float m_gridSize;     // Size of the grid
		float m_gridSpacing;  // Spacing between grid lines
		float m_gridLineWidth; // Width of the grid lines
		Color m_gridColor; // Color of the grid lines
	};
}


#endif // RENDERER__GRID_CONTROL__HPP