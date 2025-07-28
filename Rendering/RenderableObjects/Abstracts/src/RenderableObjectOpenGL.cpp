#include "../include/RenderableObjectOpenGL.hpp"
#include "../../../Light/include/LuminousBehavior.hpp"
#include "../../../Light/include/NonLuminousBehavior.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		RenderableObjectOpenGL::RenderableObjectOpenGL(const Math::Vec3& centerPosition, const Space::Color& color, const VertexLayout& vertexLayout)
			: m_luminous{ false }
			, m_stateChanged{ false }
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
			, m_pILightBehavior{ new NonLuminousBehavior() }
		{
		}

		RenderableObjectOpenGL::~RenderableObjectOpenGL() = default;

		bool RenderableObjectOpenGL::IsLuminous() const
		{
			return m_luminous;
		}

		bool RenderableObjectOpenGL::StateChanged() const
		{
			return m_stateChanged;
		}

		unsigned int RenderableObjectOpenGL::GetVBO() const
		{
			return m_VBO;
		}

		unsigned int RenderableObjectOpenGL::GetVAO() const
		{
			return m_VAO;
		}

		unsigned int RenderableObjectOpenGL::GetEBO() const
		{
			return m_EBO;
		}

		unsigned int RenderableObjectOpenGL::GetVertexCount() const
		{
			return m_vertices.size();
		}

		unsigned int RenderableObjectOpenGL::GetIndicesCount() const
		{
			return m_indices.size();
		}

		std::vector<Vertex> RenderableObjectOpenGL::GetVertices() const
		{
			return m_vertices;
		}

		std::vector<unsigned int> RenderableObjectOpenGL::GetIndices() const
		{
			return m_indices;
		}

		Math::Vec3 RenderableObjectOpenGL::GetCenterPosition() const
		{
			return MathUtils::FromGLM(m_centerPosition);
		}

		Math::Vec3 RenderableObjectOpenGL::GetRotation() const
		{
			return MathUtils::FromGLM(m_rotation);
		}

		Math::Vec3 RenderableObjectOpenGL::GetScale() const
		{
			return MathUtils::FromGLM(m_scale);
		}

		Math::Mat4 RenderableObjectOpenGL::GetModelMatrix() const
		{
			return MathUtils::FromGLM(m_modelMatrix);
		}

		Space::Color RenderableObjectOpenGL::GetColor() const
		{
			return m_color;
		}

		ILightBehavior* RenderableObjectOpenGL::GetLightBehavior() const
		{
			return m_pILightBehavior;
		}

		void RenderableObjectOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
			m_modelMatrix = MathUtils::ToGLM(modelMatrix);
			m_stateChanged = true;
		}

		void RenderableObjectOpenGL::SetLuminousBehavior(ILightBehavior* behavior)
		{
			if (behavior == nullptr)
			{
				spdlog::error("Trying to set nullptr behavior.");
				return;
			}
			delete m_pILightBehavior;
			m_pILightBehavior = behavior;
			m_luminous = dynamic_cast<LuminousBehavior*>(m_pILightBehavior) ? true : false;
			m_stateChanged = true;
		}

		void RenderableObjectOpenGL::ResetState()
		{
			m_stateChanged = false;
		}

		void RenderableObjectOpenGL::Translate(const Math::Vec3& translation)
		{
			m_centerPosition = MathUtils::ToGLM(translation);
			UpdateModelMatrix(TransformationType::TRANSLATE);
		}

		void RenderableObjectOpenGL::TranslateDelta(const Math::Vec3& translationDelta)
		{
			m_centerPosition += MathUtils::ToGLM(translationDelta);
			UpdateModelMatrix(TransformationType::TRANSLATE);
		}

		void RenderableObjectOpenGL::Rotate(const Math::Vec3& rotation)
		{
			m_rotation += MathUtils::ToGLM(rotation);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGL::RotateX(float angle)
		{
			m_rotation += glm::vec3(angle, 0.0f, 0.0f);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGL::RotateY(float angle)
		{
			m_rotation += glm::vec3(0.0f, angle, 0.0f);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGL::RotateZ(float angle)
		{
			m_rotation += glm::vec3(0.0f, 0.0f, angle);
			UpdateModelMatrix(TransformationType::ROTATE);
		}

		void RenderableObjectOpenGL::Scale(const Math::Vec3& scale)
		{
			m_scale += MathUtils::ToGLM(scale);
			UpdateModelMatrix(TransformationType::SCALE);
		}

		void RenderableObjectOpenGL::Init()
		{
			CreateAndBindVertexAttributes();
			CreateAndBindVertexBuffers(m_vertices);
			GenerateAndBindElementBuffer(m_indices);
			SetVertexAttributePointers();
			UnbindVertexAttributes();
		}

		void RenderableObjectOpenGL::CreateAndBindVertexAttributes()
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void RenderableObjectOpenGL::CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices)
		{
			// Generate and bind VBO
			glCreateBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}

		void RenderableObjectOpenGL::GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices)
		{
			// Generate and bind EBO
			glCreateBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		void RenderableObjectOpenGL::SetVertexAttributePointers()
		{
			const std::vector<VertexAttributes>& attributes = m_vertexLayout.GetVerticesAttributesVec();
			size_t stride = m_vertexLayout.GetStride();
			for (const auto& attr : attributes)
			{
				glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, stride, (void*)attr.offset);
				glEnableVertexAttribArray(attr.index);
			}
		}

		void RenderableObjectOpenGL::UnbindVertexAttributes()
		{
			// Unbind VAO
			glBindVertexArray(0);
		}

		void RenderableObjectOpenGL::UpdateModelMatrix(const TransformationType& transformationType)
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
			m_stateChanged = true;
		}

		glm::mat4 RenderableObjectOpenGL::ConstructTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), m_centerPosition);
		}

		glm::mat4 RenderableObjectOpenGL::ConstructRotationMatrix() const
		{
			return glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * // Z rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * // Y rotation
				glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X rotation;
		}

		glm::mat4 RenderableObjectOpenGL::ConstructScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), m_scale);
		}
	}
}
