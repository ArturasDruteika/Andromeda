#ifndef RENDERING__ABSTRACTS__RENDERABLE_OBJECT_OPENGL_BASE__HPP
#define RENDERING__ABSTRACTS__RENDERABLE_OBJECT_OPENGL_BASE__HPP


#include "pch.hpp"
#include "../../Vertices/include/VertexLayouts.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Andromeda/Space/Objects/IMesh.hpp"


namespace Andromeda::Rendering
{
	class RenderableObjectOpenGL
	{	
	public:
		RenderableObjectOpenGL(const IMesh& mesh, const VertexLayout& vertexLayout);
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
		void Init(const IMesh& mesh);
		void CreateAndBindVertexAttributes();
		void CreateAndBindVertexBuffers(const std::vector<Vertex>& vertices);
		void GenerateAndBindElementBuffer(const std::vector<unsigned int>& indices);
		void SetVertexAttributePointers();
		void UnbindVertexAttributes();

	protected:
		unsigned int m_VBO;
		unsigned int m_VAO;
		unsigned int m_EBO;
		VertexLayout m_vertexLayout;
	};
}


#endif // RENDERING__ABSTRACTS__RENDERABLE_OBJECT_OPENGL_BASE__HPP