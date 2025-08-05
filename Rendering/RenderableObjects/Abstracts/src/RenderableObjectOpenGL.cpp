#include "../include/RenderableObjectOpenGL.hpp"
#include "../../../Light/Abstracts/include/LuminousBehavior.hpp"
#include "../../../Light/Abstracts/include/NonLuminousBehavior.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		RenderableObjectOpenGL::RenderableObjectOpenGL(const Math::Vec3& centerPosition, const Space::Color& color, const VertexLayout& vertexLayout)
			: RenderableObject(centerPosition, color)
			, m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_EBO{ 0 }
			, m_vertexLayout{ vertexLayout }
		{
		}

		RenderableObjectOpenGL::~RenderableObjectOpenGL() = default;

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
	}
}
