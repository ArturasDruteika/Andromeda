#include "../include/Vertex.hpp"
#include "../include/VertexImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		Vertex::VertexImpl::VertexImpl(float x, float y, float z, float r, float g, float b)
			: m_position{ x, y, z }
			, m_color{ r, g, b }
		{
		}

		Vertex::VertexImpl::~VertexImpl()
		{
		}

		std::array<float, 3> Vertex::VertexImpl::GetPosition() const
		{
			return m_position;
		}

		void Vertex::VertexImpl::SetPosition(float x, float y, float z)
		{
			m_position = { x, y, z };
		}

		std::array<float, 3> Vertex::VertexImpl::GetColor() const
		{
			return m_color;
		}

		void Vertex::VertexImpl::SetColor(float r, float g, float b)
		{
			m_color = { r, g, b };
		}
	}
}
