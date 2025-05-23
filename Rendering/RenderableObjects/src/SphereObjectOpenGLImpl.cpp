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
			: m_centerPosition{ MathUtils::ToGLM(centerPosition) }
			, m_radius{ radius }
			, m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_EBO{ 0 }
			, m_rotation{ 0.0f, 0.0f, 0.0f }
			, m_scale{ 1.0f, 1.0f, 1.0f }
			, m_vertexLayout{ 
				std::vector {
					Rendering::VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0 }, // Position
					Rendering::VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), sizeof(Space::Point3D)} // Color
				} 
			}
			, m_modelMatrix{ glm::mat4(1.0f) }
		{
			ConstructSphere(radius, 200, 200, color);
			Init(m_vertices, m_indices);
			UpdateModelMatrix();
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
			return MathUtils::FromGLM(m_modelMatrix);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetRadius(float radius)
		{
			m_radius = radius;
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
			m_modelMatrix = MathUtils::ToGLM(modelMatrix);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::UpdateModelMatrix()
		{
			glm::mat4 translationMatrix = ConstructTranslationMatrix();
			glm::mat4 rotationMatrix = ConstructRotationMatrix();
			glm::mat4 scaleMatrix = ConstructScaleMatrix();
			m_modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetCenterPosition(const Math::Vec3& position, bool updateModelMatrix)
		{
			m_centerPosition = MathUtils::ToGLM(position);
			if (updateModelMatrix)
			{
				UpdateModelMatrix();
			}
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetRotation(const Math::Vec3& rotation, bool updateModelMatrix)
		{
			m_rotation = MathUtils::ToGLM(rotation);
			if (updateModelMatrix)
			{
				UpdateModelMatrix();
			}
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::SetScale(const Math::Vec3& scale, bool updateModelMatrix)
		{
			m_scale = MathUtils::ToGLM(scale);
			if (updateModelMatrix)
			{
				UpdateModelMatrix();
			}
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::Translate(const Math::Vec3& translation)
		{
			m_centerPosition = MathUtils::ToGLM(translation);
			UpdateModelMatrix();
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::TranslateDelta(const Math::Vec3& translationDelta)
		{
			m_centerPosition += MathUtils::ToGLM(translationDelta);
			UpdateModelMatrix();
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::Rotate(const Math::Vec3& rotation)
		{
			m_rotation += MathUtils::ToGLM(rotation);
			UpdateModelMatrix();
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::Scale(const Math::Vec3& scale)
		{
			m_scale += MathUtils::ToGLM(scale);
			UpdateModelMatrix();
		}

		float SphereObjectOpenGL::SphereObjectOpenGLImpl::GetRadius() const
		{
			return m_radius;
		}

		Math::Vec3 SphereObjectOpenGL::SphereObjectOpenGLImpl::GetCenterPosition() const
		{
			return MathUtils::FromGLM(m_centerPosition);
		}

		Math::Vec3 SphereObjectOpenGL::SphereObjectOpenGLImpl::GetRotation() const
		{
			return MathUtils::FromGLM(m_rotation);
		}

		Math::Vec3 SphereObjectOpenGL::SphereObjectOpenGLImpl::GetScale() const
		{
			return MathUtils::FromGLM(m_scale);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		{
			CreateAndBindVertexAttributes();
			CreateAndBindVertexBuffers(vertices);
			GenerateAndBindElementBuffer(indices);
			SetVertexAttributePointers();
			UnbindVertexAttributes();

			m_vertexCount = static_cast<unsigned int>(indices.size());
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::CreateAndBindVertexAttributes()
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices)
		{
			// Generate and bind VBO
			glCreateBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}

		void SphereObjectOpenGL::SphereObjectOpenGLImpl::GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices)
		{
			// Generate and bind EBO
			glCreateBuffers(1, &m_EBO);
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
			return glm::translate(glm::mat4(1.0f), m_centerPosition);
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
