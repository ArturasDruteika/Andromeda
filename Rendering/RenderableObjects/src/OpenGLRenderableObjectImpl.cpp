#include "../include/OpenGLRenderableObjectImpl.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLRenderableObject::OpenGLRenderableObjectImpl::OpenGLRenderableObjectImpl(
			const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices,
			const VertexLayout& layout
		)
			: m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_vertices{ vertices }
			, m_vertexCount{ static_cast<unsigned int>(indices.size()) }
			, m_vertexLayout{ layout }
		{
			Init(vertices, indices);
		}

		OpenGLRenderableObject::OpenGLRenderableObjectImpl::~OpenGLRenderableObjectImpl()
		{
			glDeleteVertexArrays(1, &m_VAO);
			glDeleteBuffers(1, &m_VBO);
		}

		unsigned int OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetVBO() const
		{
			return m_VBO;
		}

		unsigned int OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetVAO() const
		{
			return m_VAO;
		}

		unsigned int OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetEBO() const
		{
			return m_EBO;
		}

		unsigned int OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetVertexCount() const
		{
			return m_vertexCount;
		}

		std::vector<Vertex> OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetVertices() const
		{
			return m_vertices;
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		{
			GenerateAndBindVertexAttributes();
			GenerateAndBindVertexBuffers(vertices, indices);
			GenerateAndBindElementBuffer(indices);
			SetVertexAttributePointers();
			UnbindVertexAttributes();
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::GenerateAndBindVertexAttributes()
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::GenerateAndBindVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		{
			// Generate and bind VBO
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices)
		{
			// Generate and bind EBO
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetVertexAttributePointers()
		{
			const std::vector<VertexAttributes>& attributes = m_vertexLayout.GetVerticesAttributesVec();
			size_t stride = m_vertexLayout.GetStride();
			for (const auto& attr : attributes)
			{
				glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, stride, (void*)attr.offset);
				glEnableVertexAttribArray(attr.index);
			}
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::UnbindVertexAttributes()
		{
			// Unbind VAO
			glBindVertexArray(0);
		}
	}
}
