#include "../include/OpenGLRenderableObjectImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"

namespace Andromeda
{
    namespace Rendering
    {
        OpenGLRenderableObject::OpenGLRenderableObjectImpl::OpenGLRenderableObjectImpl(
            const std::vector<Space::Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            const VertexLayout& layout
        )
            : m_VBO{ 0 }
            , m_VAO{ 0 }
            , m_vertices{ vertices }
            , m_vertexCount{ static_cast<unsigned int>(indices.size()) }
            , m_vertexLayout{ layout }
            , m_modelMatrix{ glm::mat4(1.0f) } // Initialize as identity matrix
        {
            Init(vertices, indices);
            UpdateModelMatrix(); // Compute the initial model matrix
        }

        OpenGLRenderableObject::OpenGLRenderableObjectImpl::~OpenGLRenderableObjectImpl()
        {
            if (m_VAO != 0)
            {
                glDeleteVertexArrays(1, &m_VAO);
            }
            if (m_VBO != 0)
            {
                glDeleteBuffers(1, &m_VBO);
            }
            if (m_EBO != 0)
            {
                glDeleteBuffers(1, &m_EBO);
            }
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

        std::vector<Space::Vertex> OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetVertices() const
        {
            return m_vertices;
        }

        Math::Mat4 OpenGLRenderableObject::OpenGLRenderableObjectImpl::GetModelMatrix() const
        {
            return MathUtils::FromGLM(m_modelMatrix);
        }

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetModelMatrix(const Math::Mat4& modelMatrix)
        {
            m_modelMatrix = MathUtils::ToGLM(modelMatrix);
        }

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetPosition(const Math::Vec3& position, bool updateModelMatrix)
        {
            m_position = MathUtils::ToGLM(position);
            if (updateModelMatrix)
            {
                UpdateModelMatrix();
            }
        }

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetRotation(const Math::Vec3& rotation, bool updateModelMatrix)
        {
            m_rotation = MathUtils::ToGLM(rotation);
            if (updateModelMatrix)
            {
                UpdateModelMatrix();
            }
        }

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::SetScale(const Math::Vec3& scale, bool updateModelMatrix)
        {
            m_scale = MathUtils::ToGLM(scale);
            if (updateModelMatrix)
            {
                UpdateModelMatrix();
            }
        }

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::UpdateModelMatrix()
        {
            // Start with an identity matrix
            m_modelMatrix = glm::mat4(1.0f);

            // Apply transformations: scale, then rotate (Z-Y-X order), then translate
            m_modelMatrix = ConstructTranslationMatrix() * ConstructRotationMatrix() * ConstructScaleMatrix();
        }

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::Init(const std::vector<Space::Vertex>& vertices, const std::vector<unsigned int>& indices)
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

        void OpenGLRenderableObject::OpenGLRenderableObjectImpl::GenerateAndBindVertexBuffers(const std::vector<Space::Vertex>& vertices, const std::vector<unsigned int>& indices)
        {
            // Generate and bind VBO
            glGenBuffers(1, &m_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Space::Vertex), vertices.data(), GL_STATIC_DRAW);
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

        glm::mat4 OpenGLRenderableObject::OpenGLRenderableObjectImpl::ConstructTranslationMatrix() const
        {
            return glm::translate(glm::mat4(1.0f), m_position);
        }

        glm::mat4 OpenGLRenderableObject::OpenGLRenderableObjectImpl::ConstructRotationMatrix() const
        {
            return glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * // Z rotation
                glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * // Y rotation
                glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X rotation;
        }

        glm::mat4 OpenGLRenderableObject::OpenGLRenderableObjectImpl::ConstructScaleMatrix() const
        {
            return glm::scale(glm::mat4(1.0f), m_scale);
        }
    }
}