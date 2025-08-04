#include "../include/GridControl.hpp"


namespace Andromeda::Rendering
{
	GridControl::GridControl()
        : m_isGridVisible{ false }
        , m_gridSize{ 10.0f }
        , m_gridSpacing{ 1.0f }
        , m_gridLineWidth{ 0.1f }
        , m_gridColor{ 1.0f, 1.0f, 1.0f, 1.0f }
	{
	}

	GridControl::~GridControl() = default;

    bool GridControl::IsGridVisible() const
    {
        return m_isGridVisible;
    }

    float GridControl::GetGridSpacing() const
    {
        return m_gridSpacing;
    }

    float GridControl::GetGridLineWidth() const
    {
        return m_gridLineWidth;
    }

    const Space::Color& GridControl::GetGridColor() const
    {
		return m_gridColor;
    }

    void GridControl::SetGridVisible(bool isVisible)
    {
        m_isGridVisible = isVisible;
	}

    void GridControl::SetGridSize(float size)
    {
		m_gridSize = size;
    }

    void GridControl::SetGridSpacing(float spacing)
    {
		m_gridSpacing = spacing;
    }

    void GridControl::SetGridLineWidth(float lineWidth)
    {
		m_gridLineWidth = lineWidth;
    }

    void GridControl::SetGridColor(const Space::Color& color)
    {
		m_gridColor = color;
    }
}
