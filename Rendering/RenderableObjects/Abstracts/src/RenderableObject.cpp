#include "../include/RenderableObject.hpp"

namespace Andromeda::Rendering
{
	RenderableObject::RenderableObject(const Math::Vec3& centerPosition, const PhysicalProperties::Color& color)
		: Transformable(centerPosition)
		, m_color{ color }
	{
	}

	RenderableObject::~RenderableObject() = default;

	PhysicalProperties::Color RenderableObject::GetColor() const
	{
		return m_color;
	}

	void RenderableObject::SetColor(const PhysicalProperties::Color& color)
	{
		m_color = color;
	}
}
