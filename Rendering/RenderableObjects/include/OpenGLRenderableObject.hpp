#ifndef RENDERING__RENDERABLE_OBJECT__HPP
#define RENDERING__RENDERABLE_OBJECT__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "../../Vertices/include/VertexLayouts.hpp"
#include "../../Vertices/include/Vertex.hpp"
//#include "../../Math/include/MathTypes.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API OpenGLRenderableObject
		{	
		public:
			OpenGLRenderableObject(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const VertexLayout& layout);
			~OpenGLRenderableObject();

			OpenGLRenderableObject(const OpenGLRenderableObject& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderableObject& operator=(const OpenGLRenderableObject& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderableObject(OpenGLRenderableObject&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderableObject& operator=(OpenGLRenderableObject&& other) noexcept = delete;	// Prevent Move Assignment

			unsigned int GetVBO() const;
			unsigned int GetVAO() const;
			unsigned int GetEBO() const;
			unsigned int GetVertexCount() const;
			std::vector<Vertex> GetVertices() const;

			// Model matrix management
			Math::Mat4 GetModelMatrix() const;
			void SetModelMatrix(const Math::Mat4& modelMatrix); // Uncommented and will be implemented
			void UpdateModelMatrix(); // New method to compute the model matrix from position, rotation, scale

			// Transform properties (optional: you can set these directly and recompute the model matrix)
			void SetPosition(const Math::Vec3& position, bool updateModelMatrix = false);
			void SetRotation(const Math::Vec3& rotation, bool updateModelMatrix = false); // Euler angles in radians (X, Y, Z)
			void SetScale(const Math::Vec3& scale, bool updateModelMatrix = false);

		private:
			class OpenGLRenderableObjectImpl;
			OpenGLRenderableObjectImpl* m_pOpenGLRenderableObjectImpl;
		};
	}
}


#endif // RENDERING__RENDERABLE_OBJECT__HPP