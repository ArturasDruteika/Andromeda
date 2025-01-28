#include "../include/OpenGLRenderableObjectImpl.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLRenderableObject::OpenGLRenderableObjectImpl::OpenGLRenderableObjectImpl(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
			: m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_position{ 0.f }
			, m_rotation{ 0.f }
			, m_scale{ 1.f }
			, m_vertexCount{ static_cast<unsigned int>(indices.size()) }
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

		std::vector<float> OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetPosition() const
		{
			return { m_position.x, m_position.y, m_position.z };
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetPosition(float x, float y, float z)
		{
			m_position = glm::vec3(x, y, z);
		}

		std::vector<float> OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetRotation() const
		{
			return { m_rotation.x, m_rotation.y, m_rotation.z };
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetRotation(float pitch, float yaw, float roll)
		{
			m_rotation = glm::vec3(pitch, yaw, roll);
		}

		std::vector<float> OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetScale() const
		{
			return { m_scale.x, m_scale.y, m_scale.z };
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetScale(float x, float y, float z)
		{
			m_scale = glm::vec3(x, y, z);
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::Init(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
		{
			// Generate and bind VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			// Generate and bind VBO
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			// Generate and bind EBO
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			// Set vertex attribute pointers
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color
			glEnableVertexAttribArray(1);

			// Unbind VAO
			glBindVertexArray(0);
		}
	}
}
