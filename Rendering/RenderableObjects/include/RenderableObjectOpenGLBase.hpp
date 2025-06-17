#ifndef RENDERING__RENDERABLE_OBJECT_OPENGL_BASE__HPP
#define RENDERING__RENDERABLE_OBJECT_OPENGL_BASE__HPP


#include "pch.hpp"
#include "TransformationTypes.hpp"
#include "../../Vertices/include/VertexLayouts.hpp"
#include "../../Vertices/include/Vertex.hpp"
#include "../../Light/include/ILightBehavior.hpp"
#include "Colors.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RenderableObjectOpenGLBase
		{	
		public:
			RenderableObjectOpenGLBase(const Math::Vec3& centerPosition, const Space::Color& color, const VertexLayout& vertexLayout);
			~RenderableObjectOpenGLBase();

			RenderableObjectOpenGLBase(const RenderableObjectOpenGLBase& other) = delete;	// Prevent Copy Constructor
			RenderableObjectOpenGLBase& operator=(const RenderableObjectOpenGLBase& other) = delete;	// Prevent Copy Assignment
			RenderableObjectOpenGLBase(RenderableObjectOpenGLBase&& other) noexcept = delete;	// Prevent Move Constructor
			RenderableObjectOpenGLBase& operator=(RenderableObjectOpenGLBase&& other) noexcept = delete;	// Prevent Move Assignment

			// Getters
			bool IsLuminous() const;
			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;
			unsigned int GetVertexCount() const;
			unsigned int GetIndicesCount() const;
			std::vector<Vertex> GetVertices() const;
			std::vector<unsigned int> GetIndices() const;
			Math::Vec3 GetCenterPosition() const;
			Math::Vec3 GetRotation() const;
			Math::Vec3 GetScale() const;
			Math::Mat4 GetModelMatrix() const;
			Space::Color GetColor() const;
			ILightBehavior* GetLightBehavior() const;
			// Setters
			void SetLuminous(bool isEmitingLight);
			void SetModelMatrix(const Math::Mat4& modelMatrix);
			// Transformation operations
			void Translate(const Math::Vec3& translation);
			void TranslateDelta(const Math::Vec3& translationDelta);
			void Rotate(const Math::Vec3& rotation);
			void RotateX(float angle);
			void RotateY(float angle);
			void RotateZ(float angle);
			void Scale(const Math::Vec3& scale);

		protected:
			void Init();
			void CreateAndBindVertexAttributes();
			void CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices);
			void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
			void SetVertexAttributePointers();
			void UnbindVertexAttributes();

			// Transformation matrices
			void UpdateModelMatrix(const TransformationType& transformationType);
			glm::mat4 ConstructTranslationMatrix() const;
			glm::mat4 ConstructRotationMatrix() const;
			glm::mat4 ConstructScaleMatrix() const;

		protected:
			bool m_luminous;
			unsigned int m_VBO;
			unsigned int m_VAO;
			unsigned int m_EBO;
			std::vector<Vertex> m_vertices;
			std::vector<unsigned int> m_indices;
			ILightBehavior* m_pILightBehavior;
			VertexLayout m_vertexLayout;
			Space::Color m_color;

			// Transform components
			glm::vec3 m_centerPosition;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
			glm::mat4 m_translationMatrix;
			glm::mat4 m_rotationMatrix;
			glm::mat4 m_scaleMatrix;
			glm::mat4 m_modelMatrix;
		};
	}
}


#endif // RENDERING__RENDERABLE_OBJECT_OPENGL_BASE__HPP