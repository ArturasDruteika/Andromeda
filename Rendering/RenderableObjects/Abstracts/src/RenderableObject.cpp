#include "../include/RenderableObject.hpp"

namespace Andromeda::Rendering
{
	RenderableObject::RenderableObject(const Math::Vec3& centerPosition, const Space::Color& color)
		: Transformable(centerPosition)
		, m_color{ color }
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
