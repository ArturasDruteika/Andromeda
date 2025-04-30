#include "../include/SphereObjectOpenGLImpl.hpp"
#include "Constants.hpp"
#include "Points.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		SphereObjectOpenGL::SphereObjectOpenGLImpl::SphereObjectOpenGLImpl(float radius, const Space::Color& color)
			: m_vertexLayout{ std::vector {
							Rendering::VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0}, // Position
							Rendering::VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), sizeof(Space::Point3D)} } } // Color
		{
			ConstructSphere(radius, 36, 18, color);
		}

		SphereObjectOpenGL::SphereObjectOpenGLImpl::~SphereObjectOpenGLImpl()
		{
		}

		unsigned int SphereObjectOpenGL::SphereObjectOpenGLImpl::GetVBO() const
		{
			return m_VBO;
		}

		unsigned int SphereObjectOpenGL::SphereObjectOpenGLImpl::GetVAO() const
		{
			return m_VAO;
		}

		unsigned int SphereObjectOpenGL::SphereObjectOpenGLImpl::GetEBO() const
		{
			return m_EBO;
		}

		unsigned int SphereObjectOpenGL::SphereObjectOpenGLImpl::GetVertexCount() const
		{
			return m_vertexCount;
		}

		std::vector<Vertex> SphereObjectOpenGL::SphereObjectOpenGLImpl::GetVertices() const
		{
			return m_vertices;
		}

		Math::Mat4 SphereObjectOpenGL::SphereObjectOpenGLImpl::GetModelMatrix() const
		{
			return Math::Mat4();
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::UpdateModelMatrix()
		{
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetPosition(const Math::Vec3& position, bool updateModelMatrix)
		{
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetRotation(const Math::Vec3& rotation, bool updateModelMatrix)
		{
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetScale(const Math::Vec3& scale, bool updateModelMatrix)
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

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		{
			GenerateAndBindVertexAttributes();
			GenerateAndBindVertexBuffers(vertices, indices);
			GenerateAndBindElementBuffer(indices);
			SetVertexAttributePointers();
			UnbindVertexAttributes();
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::GenerateAndBindVertexAttributes()
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::GenerateAndBindVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		{
			// Generate and bind VBO
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices)
		{
			// Generate and bind EBO
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetVertexAttributePointers()
		{
			const std::vector<VertexAttributes>& attributes = m_vertexLayout.GetVerticesAttributesVec();
			size_t stride = m_vertexLayout.GetStride();
			for (const auto& attr : attributes)
			{
				glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, stride, (void*)attr.offset);
				glEnableVertexAttribArray(attr.index);
			}
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::UnbindVertexAttributes()
		{
			// Unbind VAO
			glBindVertexArray(0);
		}

		glm::mat4 SphereObjectOpenGL::SphereObjectOpenGLImpl::ConstructTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), m_position);
		}

		glm::mat4 SphereObjectOpenGL::SphereObjectOpenGLImpl::ConstructRotationMatrix() const
		{
			return glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * // Z rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * // Y rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X rotation;
		}

		glm::mat4 SphereObjectOpenGL::SphereObjectOpenGLImpl::ConstructScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), m_scale);
		}
	}
}
