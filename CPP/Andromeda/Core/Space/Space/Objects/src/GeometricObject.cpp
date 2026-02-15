#include "../include/GeometricObject.hpp"


namespace Andromeda::Space
{
	GeometricObject::GeometricObject() = default;

	GeometricObject::GeometricObject(const Color& color)
		: m_color{ color }
	{
	}

	GeometricObject::~GeometricObject() = default;

	const Mesh& GeometricObject::GetMesh() const
	{
		return m_mesh;
	}

	const Color& GeometricObject::GetColor() const
	{
		return m_color;
	}

	void GeometricObject::SetMesh(const Mesh& mesh)
	{
		m_mesh = mesh;
	}

	void GeometricObject::SetColor(const Color& color)
	{
		m_color = color;
	}
}
