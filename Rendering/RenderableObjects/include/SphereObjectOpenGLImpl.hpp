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
			SphereObjectOpenGLImpl(const Math::Vec3& centerPosition, float radius, const Space::Color& color);
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
			void SetRadius(float radius);
			void SetModelMatrix(const Math::Mat4& modelMatrix);
			void UpdateModelMatrix();
			void SetCenterPosition(const Math::Vec3& position, bool updateModelMatrix = true);
			void SetRotation(const Math::Vec3& rotation, bool updateModelMatrix = true); // Euler angles in radians (X, Y, Z)
			void SetScale(const Math::Vec3& scale, bool updateModelMatrix = true);

			// Getters
			float GetRadius() const;
			Math::Vec3 GetCenterPosition() const;
			Math::Vec3 GetRotation() const;
			Math::Vec3 GetScale() const;

		private:
			// OpenGL related members
			void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
			void CreateAndBindVertexAttributes();
			void CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices);
			void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
			void SetVertexAttributePointers();
			void UnbindVertexAttributes();

			// Transformation matrices
			glm::mat4 ConstructTranslationMatrix() const;
			glm::mat4 ConstructRotationMatrix() const;
			glm::mat4 ConstructScaleMatrix() const;

			// Sphere construction
			void ConstructSphere(float radius, int sectorCount, int stackCount, const Space::Color& color);

			float m_radius;
			unsigned int m_VBO;
			unsigned int m_VAO;
			unsigned int m_EBO;
			unsigned int m_vertexCount;
			std::vector<Vertex> m_vertices;
			std::vector<unsigned int> m_indices;
			VertexLayout m_vertexLayout;

			// Transform components
			glm::vec3 m_centerPosition;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
			glm::mat4 m_modelMatrix;
		};
	}
}


#endif // RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP