#ifndef RENDERING__CUBE_OBJECT_OPENGL__HPP
#define RENDERING__CUBE_OBJECT_OPENGL__HPP


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


#include "IRenderableObjectOpenGL.hpp"
#include "Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API CubeObjectOpenGL
			: public IRenderableObjectOpenGL
		{	
		public:
			CubeObjectOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color);
			~CubeObjectOpenGL();

			CubeObjectOpenGL(const CubeObjectOpenGL& other) = delete;	// Prevent Copy Constructor
			CubeObjectOpenGL& operator=(const CubeObjectOpenGL& other) = delete;	// Prevent Copy Assignment
			CubeObjectOpenGL(CubeObjectOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
			CubeObjectOpenGL& operator=(CubeObjectOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

			// Overrides from IRenderableObjectOpenGL
			// Getters

			unsigned int GetVBO() const override;
			unsigned int GetVAO() const override;
			unsigned int GetEBO() const override;
			unsigned int GetVertexCount() const override;
			std::vector<Vertex> GetVertices() const override;
			Math::Vec3 GetCenterPosition() const override;
			Math::Mat4 GetModelMatrix() const override;
			Space::Color GetColor() const override;
			// Setters
			void SetModelMatrix(const Math::Mat4& modelMatrix) override;
			// Transformation operations
			void Translate(const Math::Vec3& translation) override;
			void TranslateDelta(const Math::Vec3& translationDelta) override;
			void Rotate(const Math::Vec3& rotation) override;
			void RotateX(float angle) override;
			void RotateY(float angle) override;
			void RotateZ(float angle) override;
			void Scale(const Math::Vec3& scale) override;

			// Getters
			float GetHalfExtent() const;
			Math::Vec3 GetRotation() const;
			Math::Vec3 GetScale() const;

		private:
			class CubeObjectOpenGLImpl;
			CubeObjectOpenGLImpl* m_pCubeObjectOpenGLImpl;
		};
	}
}


#endif // RENDERING__CUBE_OBJECT_OPENGL__HPP