#ifndef RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP
#define RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP


#include "SphereObjectOpenGL.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class SphereObjectOpenGL::SphereObjectOpenGLImpl
		{	
		public:
			SphereObjectOpenGLImpl(float radius, const Space::Color& color);
			~SphereObjectOpenGLImpl();

			SphereObjectOpenGLImpl(const SphereObjectOpenGLImpl& other) = delete;	// Prevent Copy Constructor
			SphereObjectOpenGLImpl& operator=(const SphereObjectOpenGLImpl& other) = delete;	// Prevent Copy Assignment
			SphereObjectOpenGLImpl(SphereObjectOpenGLImpl&& other) noexcept = delete;	// Prevent Move Constructor
			SphereObjectOpenGLImpl& operator=(SphereObjectOpenGLImpl&& other) noexcept = delete;	// Prevent Move Assignment

			// Getters
			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;
			unsigned int GetVertexCount() const;
			std::vector<Vertex> GetVertices() const;
			Math::Mat4 GetModelMatrix() const;

			// Setters
			void SetModelMatrix(const Math::Mat4& modelMatrix);
			void UpdateModelMatrix();
			void SetPosition(const Math::Vec3& position, bool updateModelMatrix = false);
			void SetRotation(const Math::Vec3& rotation, bool updateModelMatrix = false); // Euler angles in radians (X, Y, Z)
			void SetScale(const Math::Vec3& scale, bool updateModelMatrix = false);

		private:
			void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
			void CreateAndBindVertexAttributes();
			void CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
			void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
			void SetVertexAttributePointers();
			void UnbindVertexAttributes();

			glm::mat4 ConstructTranslationMatrix() const;
			glm::mat4 ConstructRotationMatrix() const;
			glm::mat4 ConstructScaleMatrix() const;

			void ConstructSphere(float radius, int sectorCount, int stackCount, const Space::Color& color);

			unsigned int m_VBO;
			unsigned int m_VAO;
			unsigned int m_EBO;
			unsigned int m_vertexCount;
			std::vector<Vertex> m_vertices;
			std::vector<unsigned int> m_indices;
			glm::mat4 m_modelMatrix;
			VertexLayout m_vertexLayout;

			// Transform components
			glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
			glm::vec3 m_rotation{ 0.0f, 0.0f, 0.0f }; // Euler angles (X, Y, Z)
			glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };

		};
	}
}


#endif // RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP