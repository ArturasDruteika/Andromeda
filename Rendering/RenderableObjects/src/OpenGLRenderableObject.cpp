#include "../include/OpenGLRenderableObject.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLRenderableObject::OpenGLRenderableObject(const std::vector<float>& vertices)
			: m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_position{ 0.f }
			, m_rotation{ 0.f }
			, m_scale{ 1.f }
			, m_vertextCount{ static_cast<unsigned int>(vertices.size() / 6) }
		{
			Init(vertices);
		}

		OpenGLRenderableObject::~OpenGLRenderableObject()
		{
		}

		void OpenGLRenderableObject::Init(const std::vector<float>& vertices)
		{
			// Generate VAO and VBO
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			// Bind VAO
			glBindVertexArray(m_VAO);

			// Upload vertex data
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			// Vertex attribute pointers
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color
			glEnableVertexAttribArray(1);

			// Unbind buffers
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		unsigned int OpenGLRenderableObject::GetVBO() const
		{
			return m_VBO;
		}

		unsigned int OpenGLRenderableObject::GetVAO() const
		{
			return m_VAO;
		}

		unsigned int OpenGLRenderableObject::GetVertexCount() const
		{
			return m_vertextCount;
		}

		std::vector<float> OpenGLRenderableObject::GetPosition() const
		{
			return { m_position.x, m_position.y, m_position.z };
		}

		void OpenGLRenderableObject::SetPosition(float x, float y, float z)
		{
			m_position = glm::vec3(x, y, z);
		}

		std::vector<float> OpenGLRenderableObject::GetRotation() const
		{
			return { m_rotation.x, m_rotation.y, m_rotation.z };
		}

		void OpenGLRenderableObject::SetRotation(float pitch, float yaw, float roll)
		{
			m_rotation = glm::vec3(pitch, yaw, roll);
		}

		std::vector<float> OpenGLRenderableObject::GetScale() const
		{
			return { m_scale.x, m_scale.y, m_scale.z };
		}

		void OpenGLRenderableObject::SetScale(float x, float y, float z)
		{
			m_scale = glm::vec3(x, y, z);
		}
	}
}
