#include "../include/CubeObjectOpenGLImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include "Points.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		CubeObjectOpenGL::CubeObjectOpenGLImpl::CubeObjectOpenGLImpl(const Math::Vec3& centerPosition, float halfExtent, const Space::Color& color)
			: m_centerPosition{ MathUtils::ToGLM(centerPosition) }
			, m_halfExtent{ halfExtent }
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
			ConstructCube(halfExtent, color);
			Init(m_vertices, m_indices);
			UpdateModelMatrix(TransformationType::ALL);
		}

		CubeObjectOpenGL::CubeObjectOpenGLImpl::~CubeObjectOpenGLImpl()
		{
		}

		unsigned int CubeObjectOpenGL::CubeObjectOpenGLImpl::GetVBO() const
		{
			return m_VBO;
		}

		unsigned int CubeObjectOpenGL::CubeObjectOpenGLImpl::GetVAO() const
		{
			return m_VAO;
		}

		unsigned int CubeObjectOpenGL::CubeObjectOpenGLImpl::GetEBO() const
		{
			return m_EBO;
		}

		unsigned int CubeObjectOpenGL::CubeObjectOpenGLImpl::GetVertexCount() const
		{
			return m_vertexCount;
		}

		std::vector<Vertex> CubeObjectOpenGL::CubeObjectOpenGLImpl::GetVertices() const
		{
			return m_vertices;
		}

		Math::Mat4 CubeObjectOpenGL::CubeObjectOpenGLImpl::GetModelMatrix() const
		{
			return MathUtils::FromGLM(m_modelMatrix);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
			m_modelMatrix = MathUtils::ToGLM(modelMatrix);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::Translate(const Math::Vec3& translation)
		{
			m_centerPosition = MathUtils::ToGLM(translation);
			UpdateModelMatrix(TransformationType::TRANSLATE);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::TranslateDelta(const Math::Vec3& translationDelta)
		{
			m_centerPosition += MathUtils::ToGLM(translationDelta);
			UpdateModelMatrix(TransformationType::TRANSLATE);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::Rotate(const Math::Vec3& rotation)
		{
			m_rotation += MathUtils::ToGLM(rotation);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::RotateX(float angle)
		{
			m_rotation += glm::vec3(angle, 0.0f, 0.0f);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::RotateY(float angle)
		{
			m_rotation += glm::vec3(0.0f, angle, 0.0f);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::RotateZ(float angle)
		{
			m_rotation += glm::vec3(0.0f, 0.0f, angle);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::Scale(const Math::Vec3& scale)
		{
			m_scale += MathUtils::ToGLM(scale);
			UpdateModelMatrix(TransformationType::SCALE);
		}

		float CubeObjectOpenGL::CubeObjectOpenGLImpl::GetHalfExtent() const
		{
			return m_halfExtent;
		}

		Math::Vec3 CubeObjectOpenGL::CubeObjectOpenGLImpl::GetCenterPosition() const
		{
			return MathUtils::FromGLM(m_centerPosition);
		}

		Math::Vec3 CubeObjectOpenGL::CubeObjectOpenGLImpl::GetRotation() const
		{
			return MathUtils::FromGLM(m_rotation);
		}

		Math::Vec3 CubeObjectOpenGL::CubeObjectOpenGLImpl::GetScale() const
		{
			return MathUtils::FromGLM(m_scale);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		{
			CreateAndBindVertexAttributes();
			CreateAndBindVertexBuffers(vertices);
			GenerateAndBindElementBuffer(indices);
			SetVertexAttributePointers();
			UnbindVertexAttributes();

			m_vertexCount = static_cast<unsigned int>(indices.size());
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::CreateAndBindVertexAttributes()
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices)
		{
			// Generate and bind VBO
			glCreateBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices)
		{
			// Generate and bind EBO
			glCreateBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::SetVertexAttributePointers()
		{
			const std::vector<VertexAttributes>& attributes = m_vertexLayout.GetVerticesAttributesVec();
			size_t stride = m_vertexLayout.GetStride();
			for (const auto& attr : attributes)
			{
				glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, stride, (void*)attr.offset);
				glEnableVertexAttribArray(attr.index);
			}
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::UnbindVertexAttributes()
		{
			// Unbind VAO
			glBindVertexArray(0);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::UpdateModelMatrix(const TransformationType& transformationType)
		{
			switch (transformationType)
			{
				case TransformationType::TRANSLATE:
				{
					m_translationMatrix = ConstructTranslationMatrix();
					break;
				}
				case TransformationType::ROTATE:
				{
					m_rotationMatrix = ConstructRotationMatrix();
					break;
				}
				case TransformationType::SCALE:
				{
					m_scaleMatrix = ConstructScaleMatrix();
					break;
				}
				case TransformationType::ALL:
				{
					m_translationMatrix = ConstructTranslationMatrix();
					m_rotationMatrix = ConstructRotationMatrix();
					m_scaleMatrix = ConstructScaleMatrix();
					break;
				}
				default:
				{
					spdlog::error("Invalid transformation type");
					break;
				}
			}

			m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
		}

		glm::mat4 CubeObjectOpenGL::CubeObjectOpenGLImpl::ConstructTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), m_centerPosition);
		}

		glm::mat4 CubeObjectOpenGL::CubeObjectOpenGLImpl::ConstructRotationMatrix() const
		{
			return glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * // Z rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * // Y rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X rotation;
		}

		glm::mat4 CubeObjectOpenGL::CubeObjectOpenGLImpl::ConstructScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), m_scale);
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::ConstructCube(float halfExtent, const Space::Color& color)
		{
			const float h = halfExtent;
			std::vector<glm::vec3> cubeVerts = {
				{-h, -h, -h}, { h, -h, -h}, { h,  h, -h}, {-h,  h, -h}, // back face
				{-h, -h,  h}, { h, -h,  h}, { h,  h,  h}, {-h,  h,  h}  // front face
			};

			for (const auto& v : cubeVerts)
			{
				m_vertices.push_back(Vertex(Space::Point3D(v.x, v.y, v.z), color));
			}

			m_indices = {
				// back face
				0, 1, 2, 2, 3, 0,
				// front face
				4, 5, 6, 6, 7, 4,
				// left face
				0, 4, 7, 7, 3, 0,
				// right face
				1, 5, 6, 6, 2, 1,
				// bottom face
				0, 1, 5, 5, 4, 0,
				// top face
				3, 2, 6, 6, 7, 3
			};
		}
	}
}
