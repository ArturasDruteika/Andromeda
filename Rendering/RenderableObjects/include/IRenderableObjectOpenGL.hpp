#ifndef RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP
#define RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP


#include "pch.hpp"
#include "../../Vertices/include/VertexLayouts.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Vertex.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class IRenderableObjectOpenGL
		{	
		public:
			IRenderableObjectOpenGL();
			~IRenderableObjectOpenGL();

			// Getters
			virtual unsigned int GetVBO() const = 0;
			virtual unsigned int GetVAO() const = 0;
			virtual unsigned int GetEBO() const = 0;
			virtual unsigned int GetVertexCount() const = 0;
			virtual std::vector<Space::Vertex> GetVertices() const = 0;
			virtual Math::Mat4 GetModelMatrix() const = 0;

			// Setters
			virtual void SetModelMatrix(const Math::Mat4& modelMatrix) = 0;
			virtual void UpdateModelMatrix() = 0;
			virtual void SetPosition(const Math::Vec3& position, bool updateModelMatrix = false) = 0;
			virtual void SetRotation(const Math::Vec3& rotation, bool updateModelMatrix = false) = 0; // Euler angles in radians (X, Y, Z)
			virtual void SetScale(const Math::Vec3& scale, bool updateModelMatrix = false) = 0;
		};
	}
}


#endif // RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP