#ifndef RENDERING__VERTEX_IMPL__HPP
#define RENDERING__VERTEX_IMPL__HPP


#include "../include/Vertex.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class Vertex::VertexImpl
		{
		public:
			VertexImpl(float x, float y, float z, float r, float g, float b);
			~VertexImpl();

			VertexImpl(const VertexImpl& other) = delete;	// Prevent Copy Constructor
			VertexImpl& operator=(const VertexImpl& other) = delete;	// Prevent Copy Assignment
			VertexImpl(VertexImpl&& other) noexcept = delete;	// Prevent Move Constructor
			VertexImpl& operator=(VertexImpl&& other) noexcept = delete;	// Prevent Move Assignment

			std::array<float, 3> GetPosition() const;
			void SetPosition(float x, float y, float z);
			std::array<float, 3> GetColor() const;
			void SetColor(float r, float g, float b);

		private:
			std::array<float, 3> m_position;
			std::array<float, 3> m_color;
		};
	}
}


#endif // RENDERING__VERTEX_IMPL__HPP