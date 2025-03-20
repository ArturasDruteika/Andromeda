#ifndef RENDERING__RENDERABLE_OBJECT_IMPL__HPP
#define RENDERING__RENDERABLE_OBJECT_IMPL__HPP


#include "../include/OpenGLRenderableObject.hpp"
#include "../../Vertices/include/Vertex.hpp"
#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class OpenGLRenderableObject::OpenGLRenderableObjectImpl
		{
		public:
			OpenGLRenderableObjectImpl(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const VertexLayout& layout);
			~OpenGLRenderableObjectImpl();

			OpenGLRenderableObjectImpl(const OpenGLRenderableObjectImpl& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderableObjectImpl& operator=(const OpenGLRenderableObjectImpl& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderableObjectImpl(OpenGLRenderableObjectImpl&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderableObjectImpl& operator=(OpenGLRenderableObjectImpl&& other) noexcept = delete;	// Prevent Move Assignment

			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;
			unsigned int GetVertexCount() const;
			std::vector<Vertex> GetVertices() const;

		private:
			void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
			void GenerateAndBindVertexAttributes();
			void GenerateAndBindVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
			void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
			void SetVertexAttributePointers();
			void UnbindVertexAttributes();

			unsigned int m_VBO;
			unsigned int m_VAO;
			unsigned int m_EBO;
			unsigned int m_vertexCount;
			std::vector<Vertex> m_vertices;
			VertexLayout m_vertexLayout;
		};
	}
}


#endif // RENDERING__RENDERABLE_OBJECT_IMPL__HPP