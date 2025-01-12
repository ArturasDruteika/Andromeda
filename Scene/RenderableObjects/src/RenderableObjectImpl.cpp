#include "../include/RenderableObjectImpl.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Scene
	{
		OpenGLRenderableObject::OpenGLRenderableObjectImpl::OpenGLRenderableObjectImpl(const std::vector<float>& vertices)
			: m_VBO{ 0 }
			, m_VAO{ 0 }
			, m_position{ 0.f }
			, m_rotation{ 0.f }
			, m_scale{ 1.f }
			, m_vertextCount{ 0 }
		{
			Init(vertices);
		}

		OpenGLRenderableObject::OpenGLRenderableObjectImpl::~OpenGLRenderableObjectImpl()
		{
		}

		void OpenGLRenderableObject::OpenGLRenderableObjectImpl::Init(const std::vector<float>& vertices)
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
	}
}
