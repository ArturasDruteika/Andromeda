#ifndef RENDERING__RENDERABLE_OBJECT_IMPL__HPP
#define RENDERING__RENDERABLE_OBJECT_IMPL__HPP


#include "../include/OpenGLRenderableObject.hpp"
#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class OpenGLRenderableObject::OpenGLRenderableObjectImpl
		{
		public:
			OpenGLRenderableObjectImpl(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const VertexLayout& layout);
			~OpenGLRenderableObjectImpl();

			OpenGLRenderableObjectImpl(const OpenGLRenderableObjectImpl& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderableObjectImpl& operator=(const OpenGLRenderableObjectImpl& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderableObjectImpl(OpenGLRenderableObjectImpl&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderableObjectImpl& operator=(OpenGLRenderableObjectImpl&& other) noexcept = delete;	// Prevent Move Assignment

			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;
			unsigned int GetVertexCount() const;
			std::vector<float> GetPosition() const;
			void SetPosition(float x, float y, float z);
			std::vector<float> GetRotation() const;
			void SetRotation(float pitch, float yaw, float roll);
			std::vector<float> GetScale() const;
			void SetScale(float x, float y, float z);

		private:
			void Init(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
			void GenerateAndBindVertexAttributes();
			void GenerateAndBindVertexBuffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
			void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
			void SetVertexAttributePointers();
			void UnbindVertexAttributes();

			unsigned int m_VBO;
			unsigned int m_VAO;
			unsigned int m_EBO;
			unsigned int m_vertexCount;
			glm::vec3 m_position;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
			VertexLayout m_vertexLayout;
		};
	}
}


#endif // RENDERING__RENDERABLE_OBJECT_IMPL__HPP