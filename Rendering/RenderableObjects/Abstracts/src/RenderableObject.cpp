#include "../include/RenderableObject.hpp"

namespace Andromeda::Rendering
{
	RenderableObject::RenderableObject()
	{
	}

	RenderableObject::~RenderableObject() = default;

	Space::Color RenderableObject::GetColor() const
	{
		return m_color;
	}

	void RenderableObject::SetColor(const Space::Color& color)
	{
		m_color = color;
	}
}
