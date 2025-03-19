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
			VertexImpl(const Point3D& point3D, const Color& color);
			~VertexImpl();

			VertexImpl(const VertexImpl& other);
			VertexImpl& operator=(const VertexImpl& other) = delete;	// Prevent Copy Assignment
			VertexImpl(VertexImpl&& other) noexcept = delete;	// Prevent Move Constructor
			VertexImpl& operator=(VertexImpl&& other) noexcept = delete;	// Prevent Move Assignment

			Point3D GetPosition() const;
			void SetPosition(const Point3D& color);
			Color GetColor() const;
			void SetColor(const Color& color);

		private:
			Point3D m_position;
			Color m_color;
		};
	}
}


#endif // RENDERING__VERTEX_IMPL__HPP