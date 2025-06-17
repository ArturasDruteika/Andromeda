#include "../include/RenderableObjectOpenGLBase.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		RenderableObjectOpenGLBase::RenderableObjectOpenGLBase(const Math::Vec3& centerPosition, const Space::Color& color, const VertexLayout& vertexLayout)
			: m_luminous{ false }
			, m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_EBO{ 0 }
			, m_centerPosition{ MathUtils::ToGLM(centerPosition) }
			, m_rotation{ 0.0f, 0.0f, 0.0f }
			, m_scale{ 1.0f, 1.0f, 1.0f }
			, m_vertexLayout{ vertexLayout }
			, m_modelMatrix{ glm::mat4(1.0f) }
			, m_color{ color }
			, m_translationMatrix{}
			, m_rotationMatrix{}
			, m_scaleMatrix{}
			, m_pILightBehavior{ nullptr }
		{
		}

		RenderableObjectOpenGLBase::~RenderableObjectOpenGLBase() = default;

		bool RenderableObjectOpenGLBase::IsLuminous() const
		{
			return m_luminous;
		}

		unsigned int RenderableObjectOpenGLBase::GetVBO() const
		{
			return m_VBO;
		}

		unsigned int RenderableObjectOpenGLBase::GetVAO() const
		{
			return m_VAO;
		}

		unsigned int RenderableObjectOpenGLBase::GetEBO() const
		{
			return m_EBO;
		}

		unsigned int RenderableObjectOpenGLBase::GetVertexCount() const
		{
			return static_cast<unsigned int>(m_vertices.size());
		}

		unsigned int RenderableObjectOpenGLBase::GetIndicesCount() const
		{
			return static_cast<unsigned int>(m_indices.size());
		}

		std::vector<Vertex> RenderableObjectOpenGLBase::GetVertices() const
		{
			return m_vertices;
		}

		std::vector<unsigned int> RenderableObjectOpenGLBase::GetIndices() const
		{
			return m_indices;
		}

		Math::Vec3 RenderableObjectOpenGLBase::GetCenterPosition() const
		{
			return MathUtils::FromGLM(m_centerPosition);
		}

		Math::Mat4 RenderableObjectOpenGLBase::GetModelMatrix() const
		{
			return MathUtils::FromGLM(m_modelMatrix);
		}

		Space::Color RenderableObjectOpenGLBase::GetColor() const
		{
			return m_color;
		}

		ILightBehavior* RenderableObjectOpenGLBase::GetLightBehavior() const
		{
			return m_pILightBehavior;
		}

		void RenderableObjectOpenGLBase::SetLuminous(bool isEmitingLight)
		{
			if (m_luminous != isEmitingLight)
			{
				delete m_pILightBehavior;
				
			}
			m_luminous = isEmitingLight;
		}

		void RenderableObjectOpenGLBase::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
			m_modelMatrix = MathUtils::ToGLM(modelMatrix);
		}

		void RenderableObjectOpenGLBase::Translate(const Math::Vec3& translation)
		{
			m_centerPosition = MathUtils::ToGLM(translation);
			UpdateModelMatrix(TransformationType::TRANSLATE);
		}

		void RenderableObjectOpenGLBase::TranslateDelta(const Math::Vec3& translationDelta)
		{
			m_centerPosition += MathUtils::ToGLM(translationDelta);
			UpdateModelMatrix(TransformationType::TRANSLATE);
		}

		void RenderableObjectOpenGLBase::Rotate(const Math::Vec3& rotation)
		{
			m_rotation += MathUtils::ToGLM(rotation);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGLBase::RotateX(float angle)
		{
			m_rotation += glm::vec3(angle, 0.0f, 0.0f);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGLBase::RotateY(float angle)
		{
			m_rotation += glm::vec3(0.0f, angle, 0.0f);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGLBase::RotateZ(float angle)
		{
			m_rotation += glm::vec3(0.0f, 0.0f, angle);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGLBase::Scale(const Math::Vec3& scale)
		{
			m_scale += MathUtils::ToGLM(scale);
			UpdateModelMatrix(TransformationType::SCALE);
		}

		Math::Vec3 RenderableObjectOpenGLBase::GetRotation() const
		{
			return MathUtils::FromGLM(m_rotation);
		}

		Math::Vec3 RenderableObjectOpenGLBase::GetScale() const
		{
			return MathUtils::FromGLM(m_scale);
		}

		void RenderableObjectOpenGLBase::Init()
		{
			CreateAndBindVertexAttributes();
			CreateAndBindVertexBuffers(m_vertices);
			GenerateAndBindElementBuffer(m_indices);
			SetVertexAttributePointers();
			UnbindVertexAttributes();
		}

		void RenderableObjectOpenGLBase::CreateAndBindVertexAttributes()
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void RenderableObjectOpenGLBase::CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices)
		{
			// Generate and bind VBO
			glCreateBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}

		void RenderableObjectOpenGLBase::GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices)
		{
			// Generate and bind EBO
			glCreateBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		void RenderableObjectOpenGLBase::SetVertexAttributePointers()
		{
			const std::vector<VertexAttributes>& attributes = m_vertexLayout.GetVerticesAttributesVec();
			size_t stride = m_vertexLayout.GetStride();
			for (const auto& attr : attributes)
			{
				glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, stride, (void*)attr.offset);
				glEnableVertexAttribArray(attr.index);
			}
		}

		void RenderableObjectOpenGLBase::UnbindVertexAttributes()
		{
			// Unbind VAO
			glBindVertexArray(0);
		}

		void RenderableObjectOpenGLBase::UpdateModelMatrix(const TransformationType& transformationType)
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

		glm::mat4 RenderableObjectOpenGLBase::ConstructTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), m_centerPosition);
		}

		glm::mat4 RenderableObjectOpenGLBase::ConstructRotationMatrix() const
		{
			return glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * // Z rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * // Y rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X rotation;
		}

		glm::mat4 RenderableObjectOpenGLBase::ConstructScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), m_scale);
		}
	}
}
