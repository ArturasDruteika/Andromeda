#include "../include/SphereObjectOpenGLImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include "Points.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		SphereObjectOpenGL::SphereObjectOpenGLImpl::SphereObjectOpenGLImpl(const Math::Vec3& centerPosition, float radius, const Space::Color& color)
			: m_radius{ radius }
			, RenderableObjectOpenGLBase(
				centerPosition,
				color,
				std::vector {
					Rendering::VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0 }, // Position
					Rendering::VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), sizeof(Space::Point3D)} // Color
				} 
			)
		{
			ConstructSphere(radius, 200, 200, color);
			Init(m_vertices, m_indices);
			UpdateModelMatrix(TransformationType::ALL);
		}

		SphereObjectOpenGL::SphereObjectOpenGLImpl::~SphereObjectOpenGLImpl() = default;

		float SphereObjectOpenGL::SphereObjectOpenGLImpl::GetRadius() const
		{
			return m_radius;
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetRadius(float radius)
		{
			
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::ConstructSphere(float radius, int sectorCount, int stackCount, const Space::Color& color)
		{
			for (int i = 0; i <= stackCount; ++i)
			{
				float stackAngle = Math::PI / 2 - i * Math::PI / stackCount;
				float xy = radius * cosf(stackAngle);
				float z = radius * sinf(stackAngle);

				for (int j = 0; j <= sectorCount; ++j)
				{
					float sectorAngle = j * 2 * Math::PI / sectorCount;
					float x = xy * cosf(sectorAngle);
					float y = xy * sinf(sectorAngle);
					m_vertices.push_back(Vertex(Space::Point3D(x, y, z), color));
				}
			}

			for (int i = 0; i < stackCount; ++i)
			{
				int k1 = i * (sectorCount + 1);
				int k2 = k1 + sectorCount + 1;

				for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
				{
					if (i != 0)
					{
						m_indices.push_back(k1);
						m_indices.push_back(k2);
						m_indices.push_back(k1 + 1);
					}

					if (i != (stackCount - 1))
					{
						m_indices.push_back(k1 + 1);
						m_indices.push_back(k2);
						m_indices.push_back(k2 + 1);
					}
				}
			}
		}
	}
}
