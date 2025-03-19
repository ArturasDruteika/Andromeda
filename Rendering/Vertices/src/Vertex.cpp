#include "../include/Vertex.hpp"
#include "../include/VertexImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		Vertex::Vertex(const Point3D& point3D, const Color& color)
			: m_pVertexImpl{ new VertexImpl(point3D, color) }
		{
		}

		Vertex::~Vertex()
		{
			delete m_pVertexImpl;
		}

		Vertex::Vertex(const Vertex& other)
		{
			m_pVertexImpl = new VertexImpl(*other.m_pVertexImpl);
		}

		Point3D Vertex::GetPosition() const
		{
			return m_pVertexImpl->GetPosition();
		}

		void Vertex::SetPosition(const Point3D& point3D)
		{
			m_pVertexImpl->SetPosition(point3D);
		}

		Color Vertex::GetColor() const
		{
			return m_pVertexImpl->GetColor();
		}

		void Vertex::SetColor(const Color& color)
		{
			m_pVertexImpl->SetColor(color);
		}
	}
}
