#ifndef RENDERING__SPHERE_OBJECT_OPENGL__HPP
#define RENDERING__SPHERE_OBJECT_OPENGL__HPP


#include "IRenderableObjectOpenGL.hpp"
#include "Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class SphereObjectOpenGL 
			: public IRenderableObjectOpenGL
		{	
		public:
			SphereObjectOpenGL(float radius, const Space::Color& color);
			~SphereObjectOpenGL();

			SphereObjectOpenGL(const SphereObjectOpenGL& other) = delete;	// Prevent Copy Constructor
			SphereObjectOpenGL& operator=(const SphereObjectOpenGL& other) = delete;	// Prevent Copy Assignment
			SphereObjectOpenGL(SphereObjectOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
			SphereObjectOpenGL& operator=(SphereObjectOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

			// Getters
			unsigned int GetVBO() const override;
			unsigned int GetVAO() const override;
			unsigned int GetEBO() const override;
			unsigned int GetVertexCount() const override;
			std::vector<Vertex> GetVertices() const override;
			Math::Mat4 GetModelMatrix() const override;

			// Setters
			void SetModelMatrix(const Math::Mat4& modelMatrix) override;
			void UpdateModelMatrix() override;
			void SetPosition(const Math::Vec3& position, bool updateModelMatrix = false) override;
			void SetRotation(const Math::Vec3& rotation, bool updateModelMatrix = false) override; // Euler angles in radians (X, Y, Z)
			void SetScale(const Math::Vec3& scale, bool updateModelMatrix = false) override;

		private:
			class SphereObjectOpenGLImpl;
			SphereObjectOpenGLImpl* m_pSphereObjectOpenGLImpl;

		};
	}
}


#endif // RENDERING__SPHERE_OBJECT_OPENGL__HPP