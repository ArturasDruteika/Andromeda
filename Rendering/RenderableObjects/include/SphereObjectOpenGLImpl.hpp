#ifndef RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP
#define RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP


#include "SphereObjectOpenGL.hpp"
#include "RenderableObjectOpenGLBase.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class SphereObjectOpenGL::SphereObjectOpenGLImpl
			: public RenderableObjectOpenGLBase
		{	
		public:
			SphereObjectOpenGLImpl(const Math::Vec3& centerPosition, float radius, const Space::Color& color);
			~SphereObjectOpenGLImpl();

			SphereObjectOpenGLImpl(const SphereObjectOpenGLImpl& other) = delete;	// Prevent Copy Constructor
			SphereObjectOpenGLImpl& operator=(const SphereObjectOpenGLImpl& other) = delete;	// Prevent Copy Assignment
			SphereObjectOpenGLImpl(SphereObjectOpenGLImpl&& other) noexcept = delete;	// Prevent Move Constructor
			SphereObjectOpenGLImpl& operator=(SphereObjectOpenGLImpl&& other) noexcept = delete;	// Prevent Move Assignment

			float GetRadius() const;
			void SetRadius(float radius);

		private:
			// Sphere construction
			void ConstructSphere(float radius, int sectorCount, int stackCount, const Space::Color& color);

		private:
			float m_radius;
		};
	}
}


#endif // RENDERING__SPHERE_OBJECT_OPENGL_IMPL__HPP