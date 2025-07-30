#ifndef RENDERING__OBJECTS__CUBE_OBJECT_OPENGL__HPP
#define RENDERING__OBJECTS__CUBE_OBJECT_OPENGL__HPP


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


#include "../../Interfaces/include/IRenderableObjectOpenGL.hpp"
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

			// === Overrides from ILuminous ===
			bool IsLuminous() const override;
			ILightBehavior* GetLightBehavior() const override;
			void SetLuminousBehavior(ILightBehavior* behavior) override;

			// === Overrides from ITransformable ===
			bool StateChanged() const override;
			Math::Vec3 GetCenterPosition() const override;
			Math::Mat4 GetModelMatrix() const override;
			void SetModelMatrix(const Math::Mat4& modelMatrix) override;
			void ResetState() override;
			void Translate(const Math::Vec3& translation) override;
			void TranslateDelta(const Math::Vec3& translationDelta) override;
			void Rotate(const Math::Vec3& rotation) override;
			void RotateX(float angle) override;
			void RotateY(float angle) override;
			void RotateZ(float angle) override;
			void Scale(const Math::Vec3& scale) override;

			// === Overrides from IGeometry ===
			unsigned int GetVerticesCount() const override;
			unsigned int GetIndicesCount() const override;
			std::vector<unsigned int> GetIndices() const override;
			std::vector<Vertex> GetVertices() const override;

			// === Overrides from IRenderableObject ===
			Space::Color GetColor() const override;
			void SetColor(const Space::Color& color) override;

			// === Overrides from IRenderableObjectOpenGL ===
			unsigned int GetVBO() const override;
			unsigned int GetVAO() const override;
			unsigned int GetEBO() const override;

			// Getters
			float GetHalfExtent() const;

		private:
			class CubeObjectOpenGLImpl;
			CubeObjectOpenGLImpl* m_pCubeObjectOpenGLImpl;
		};
	}
}


#endif // RENDERING__OBJECTS__CUBE_OBJECT_OPENGL__HPP