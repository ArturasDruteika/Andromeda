#ifndef RENDERING__ABSTRACTS__RENDERABLE_OBJECT_OPENGL_BASE__HPP
#define RENDERING__ABSTRACTS__RENDERABLE_OBJECT_OPENGL_BASE__HPP


#include "pch.hpp"
#include "RenderableObject.hpp"
#include "../../../Vertices/include/VertexLayouts.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RenderableObjectOpenGL
			: public RenderableObject
		{	
		public:
			RenderableObjectOpenGL(const Math::Vec3& centerPosition, const Space::Color& color, const VertexLayout& vertexLayout);
			~RenderableObjectOpenGL();

			RenderableObjectOpenGL(const RenderableObjectOpenGL& other) = delete;	// Prevent Copy Constructor
			RenderableObjectOpenGL& operator=(const RenderableObjectOpenGL& other) = delete;	// Prevent Copy Assignment
			RenderableObjectOpenGL(RenderableObjectOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
			RenderableObjectOpenGL& operator=(RenderableObjectOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

			// Getters
			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;

		protected:
			void Init();
			void CreateAndBindVertexAttributes();
			void CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices);
			void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
			void SetVertexAttributePointers();
			void UnbindVertexAttributes();

		protected:
			unsigned int m_VBO;
			unsigned int m_VAO;
			unsigned int m_EBO;
		};
	}
}


#endif // RENDERING__ABSTRACTS__RENDERABLE_OBJECT_OPENGL_BASE__HPP