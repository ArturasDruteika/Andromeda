#include "../include/GeometricObject.hpp"


namespace Andromeda::Space
{
	GeometricObject::GeometricObject() = default;

	GeometricObject::GeometricObject(const Math::Vec3& centerPosition)
		: Transformable{ centerPosition }
	{
	}

	GeometricObject::~GeometricObject() = default;

	const Mesh& GeometricObject::GetMesh() const
	{
		return m_mesh;
	}

	Color GeometricObject::GetColor() const
	{
		return m_color;
	}

	void GeometricObject::SetColor(const Color& color)
	{
		m_color = color;
	}
}
