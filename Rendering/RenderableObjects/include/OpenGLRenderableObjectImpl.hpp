#ifndef RENDERING__RENDERABLE_OBJECT_IMPL__HPP
#define RENDERING__RENDERABLE_OBJECT_IMPL__HPP

#include "../include/OpenGLRenderableObject.hpp"
#include "../../Vertices/include/Vertex.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" // For glm::translate, glm::rotate, glm::scale

namespace Andromeda
{
    namespace Rendering
    {
        class OpenGLRenderableObject::OpenGLRenderableObjectImpl
        {
        public:
            OpenGLRenderableObjectImpl(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const VertexLayout& layout);
            ~OpenGLRenderableObjectImpl();

            OpenGLRenderableObjectImpl(const OpenGLRenderableObjectImpl& other) = delete;    // Prevent Copy Constructor
            OpenGLRenderableObjectImpl& operator=(const OpenGLRenderableObjectImpl& other) = delete;    // Prevent Copy Assignment
            OpenGLRenderableObjectImpl(OpenGLRenderableObjectImpl&& other) noexcept = delete;    // Prevent Move Constructor
            OpenGLRenderableObjectImpl& operator=(OpenGLRenderableObjectImpl&& other) noexcept = delete;    // Prevent Move Assignment

            unsigned int GetVBO() const;
            unsigned int GetVAO() const;
            unsigned int GetEBO() const;
            unsigned int GetVertexCount() const;
            std::vector<Vertex> GetVertices() const;

            // Model matrix management
            Mat4 GetModelMatrix() const;
            void SetModelMatrix(const Mat4& modelMatrix); // Uncommented and will be implemented
            void UpdateModelMatrix(); // New method to compute the model matrix from position, rotation, scale

            // Transform properties (optional: you can set these directly and recompute the model matrix)
            void SetPosition(const Vec3& position, bool updateModelMatrix = false);
            void SetRotation(const Vec3& rotation, bool updateModelMatrix = false); // Euler angles in radians (X, Y, Z)
            void SetScale(const Vec3& scale, bool updateModelMatrix = false);

        private:
            void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
            void GenerateAndBindVertexAttributes();
            void GenerateAndBindVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
            void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
            void SetVertexAttributePointers();
            void UnbindVertexAttributes();

			glm::mat4 ConstructTranslationMatrix() const;
			glm::mat4 ConstructRotationMatrix() const;
		    glm::mat4 ConstructScaleMatrix() const;

            unsigned int m_VBO;
            unsigned int m_VAO;
            unsigned int m_EBO;
            unsigned int m_vertexCount;
            std::vector<Vertex> m_vertices;
            glm::mat4 m_modelMatrix;
            VertexLayout m_vertexLayout;

            // Transform components
            glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
            glm::vec3 m_rotation{ 0.0f, 0.0f, 0.0f }; // Euler angles (X, Y, Z)
            glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
        };
    }
}

#endif // RENDERING__RENDERABLE_OBJECT_IMPL__HPP