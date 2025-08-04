#include "../include/SizeControl.hpp"


namespace Andromeda::Rendering
{
	SizeControl::SizeControl(int width, int height)
		: m_width{ width }
		, m_height{ height }
	{
	}

	SizeControl::~SizeControl() = default;

	int SizeControl::GetWidth() const
	{
		return m_width;
	}

	int SizeControl::GetHeight() const
	{
		return m_height;
	}

	void SizeControl::Resize(int width, int height)
	{
		if (width <= 0 || height <= 0)
		{
			spdlog::error("Invalid dimensions for resizing: {}x{}", width, height);
			return;
		}
		m_width = width;
		m_height = height;
	}
}
