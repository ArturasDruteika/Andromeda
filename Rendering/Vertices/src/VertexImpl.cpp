#include "../include/Vertex.hpp"
#include "../include/VertexImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		Vertex::VertexImpl::VertexImpl(const Point3D& point3D, const Color& color)
			: m_position{ point3D }
			, m_color{ color }
		{
		}

		Vertex::VertexImpl::~VertexImpl()
		{
		}

		Vertex::VertexImpl::VertexImpl(const VertexImpl& other)
			: m_position(other.m_position)
			, m_color(other.m_color)
		{
		}

		Point3D Vertex::VertexImpl::GetPosition() const
		{
			return m_position;
		}

		void Vertex::VertexImpl::SetPosition(const Point3D& point3D)
		{
			m_position = point3D;
		}

		Color Vertex::VertexImpl::GetColor() const
		{
			return m_color;
		}

		void Vertex::VertexImpl::SetColor(const Color& color)
		{
			m_color = color;
		}
	}
}
