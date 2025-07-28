#ifndef RENDERING__OBJECTS__CUBE_OBJECT_OPENGL_IMPL__HPP
#define RENDERING__OBJECTS__CUBE_OBJECT_OPENGL_IMPL__HPP


#include "CubeObjectOpenGL.hpp"
#include "../../Abstracts/include/RenderableObjectOpenGL.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class CubeObjectOpenGL::CubeObjectOpenGLImpl
			: public RenderableObjectOpenGL
		{	
		public:
			CubeObjectOpenGLImpl(const Math::Vec3& centerPosition, float radius, const Space::Color& color);
			~CubeObjectOpenGLImpl();

			CubeObjectOpenGLImpl(const CubeObjectOpenGLImpl& other) = delete;	// Prevent Copy Constructor
			CubeObjectOpenGLImpl& operator=(const CubeObjectOpenGLImpl& other) = delete;	// Prevent Copy Assignment
			CubeObjectOpenGLImpl(CubeObjectOpenGLImpl&& other) noexcept = delete;	// Prevent Move Constructor
			CubeObjectOpenGLImpl& operator=(CubeObjectOpenGLImpl&& other) noexcept = delete;	// Prevent Move Assignment

			// Getters
			float GetHalfExtent() const;
			void SetHalfExtent(float halfExtent);

		private:
			// Cube construction
			void ConstructCube(float halfExtent, const Space::Color& color);

		private:
			float m_halfExtent;
		};
	}
}


#endif // RENDERING__OBJECTS__CUBE_OBJECT_OPENGL_IMPL__HPP