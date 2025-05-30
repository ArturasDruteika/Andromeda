#include "../include/GridOpenGL.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		GridOpenGL::GridOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color)
			: RenderableObjectOpenGLBase(
				centerPosition,
				color,
				std::vector{
					VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 }, // Position
					VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D)}, // Color
					VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D) + sizeof(Space::Color)} // Normal
				}
			)
		{
		}

		GridOpenGL::~GridOpenGL() = default;

        void GridOpenGL::ConstructGrid(int size, const Space::Color& gridColor)
        {
            m_vertices.clear();
            m_indices.clear();

            uint32_t index = 0;

            for (int i = -size; i <= size; ++i)
            {
                Space::Color color = gridColor;

                // Optional: Highlight center lines with different color
                if (i == 0)
                {
                    color = Space::Color(1.0f, 0.0f, 0.0f); // X-axis = Red
                }

                // Line parallel to Z-axis (X is constant)
                m_vertices.emplace_back(Space::Point3D((float)i, 0.0f, -size), color);
                m_vertices.emplace_back(Space::Point3D((float)i, 0.0f, size), color);
                m_indices.push_back(index++);
                m_indices.push_back(index++);

                // Line parallel to X-axis (Z is constant)
                color = (i == 0) ? Space::Color(0.0f, 0.0f, 1.0f) : gridColor; // Z-axis = Blue
                m_vertices.emplace_back(Space::Point3D(-size, 0.0f, (float)i), color);
                m_vertices.emplace_back(Space::Point3D(size, 0.0f, (float)i), color);
                m_indices.push_back(index++);
                m_indices.push_back(index++);
            }
        }

	}
}
