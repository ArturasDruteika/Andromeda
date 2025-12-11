#include "../include/GeometricObject.hpp"


namespace Andromeda::Space
{
	GeometricObject::GeometricObject(const Math::Vec3& centerPosition)
		: Transformable(centerPosition)
	{
	}

	GeometricObject::~GeometricObject() = default;

	const Mesh& GeometricObject::GetMesh() const
	{
		return m_mesh;
	}

	Space::Color GeometricObject::GetColor() const
	{
		return m_color;
	}

	void GeometricObject::SetColor(const Space::Color& color)
	{
		m_color = color;
	}
}
