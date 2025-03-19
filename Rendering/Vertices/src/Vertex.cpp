#include "../include/Vertex.hpp"
#include "../include/VertexImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		Vertex::Vertex(float x, float y, float z, float r, float g, float b)
			: m_pVertexImpl{ new VertexImpl(x, y, z, r, g, b) }
		{
		}

		Vertex::~Vertex()
		{
			delete m_pVertexImpl;
		}

		std::array<float, 3> Vertex::GetPosition() const
		{
			return m_pVertexImpl->GetPosition();
		}

		void Vertex::SetPosition(float x, float y, float z)
		{
			m_pVertexImpl->SetPosition(x, y, z);
		}

		std::array<float, 3> Vertex::GetColor() const
		{
			return m_pVertexImpl->GetColor();
		}

		void Vertex::SetColor(float r, float g, float b)
		{
			m_pVertexImpl->SetColor(r, g, b);
		}
	}
}
