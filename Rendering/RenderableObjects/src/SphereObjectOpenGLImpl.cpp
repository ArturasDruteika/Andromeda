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
					VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 }, // Position
					VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D)}, // Color
                    VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D) + sizeof(Space::Color)} // Normal
				} 
			)
		{
			ConstructSphere(radius, 200, 200, color);
			Init();
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
            m_vertices.clear();
            m_indices.clear();

            // Vertex generation
            for (int i = 0; i <= stackCount; ++i)
            {
                float stackAngle = Math::PI / 2 - i * Math::PI / stackCount; // from +pi/2 to -pi/2
                float xy = radius * cosf(stackAngle); // project to X-Y plane
                float z = radius * sinf(stackAngle);  // height

                for (int j = 0; j <= sectorCount; ++j)
                {
                    float sectorAngle = j * 2 * Math::PI / sectorCount; // from 0 to 2pi
                    float x = xy * cosf(sectorAngle);
                    float y = xy * sinf(sectorAngle);

                    glm::vec3 position = { x, y, z };
                    glm::vec3 normal = glm::normalize(position); // smooth shading

                    // Use your Vertex constructor with position, color, and normal
                    m_vertices.emplace_back(
                        Space::Point3D(position.x, position.y, position.z),
                        color,
                        MathUtils::FromGLM(normal)
                    );
                }
            }

            // Index generation
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
