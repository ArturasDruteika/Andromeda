#ifndef RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP
#define RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP



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
#include "../../Light/include/ILightBehavior.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API IRenderableObjectOpenGL
		{	
		public:
			IRenderableObjectOpenGL();
			virtual ~IRenderableObjectOpenGL();

			// Getters
			virtual bool IsLuminous() const = 0;
			virtual bool StateChanged() const = 0;
			virtual unsigned int GetVBO() const = 0;
			virtual unsigned int GetVAO() const = 0;
			virtual unsigned int GetEBO() const = 0;
			virtual unsigned int GetVertexCount() const = 0;
			virtual unsigned int GetIndicesCount() const = 0;
			virtual std::vector<Vertex> GetVertices() const = 0;
			virtual Math::Vec3 GetCenterPosition() const = 0;
			virtual Math::Mat4 GetModelMatrix() const = 0;
			virtual Space::Color GetColor() const = 0;
			virtual ILightBehavior* GetLightBehavior() const = 0;
			// Setters
			virtual void SetModelMatrix(const Math::Mat4& modelMatrix) = 0;
			virtual void SetLuminousBehavior(ILightBehavior* behavior) = 0;
			virtual void ResetState() = 0;
			// Transformation operations
			virtual void Translate(const Math::Vec3& translation) = 0;
			virtual void TranslateDelta(const Math::Vec3& translationDelta) = 0;
			virtual void Rotate(const Math::Vec3& rotation) = 0;
			virtual void RotateX(float angle) = 0;
			virtual void RotateY(float angle) = 0;
			virtual void RotateZ(float angle) = 0;
			virtual void Scale(const Math::Vec3& scale) = 0;
		};
	}
}


#endif // RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP