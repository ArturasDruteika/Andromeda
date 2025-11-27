#ifndef RENDERING__OBJECTS__SPHERE_OBJECT_OPENGL__HPP
#define RENDERING__OBJECTS__SPHERE_OBJECT_OPENGL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "Space/Colors/include/Colors.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API SphereObjectOpenGL
		: public IRenderableObjectOpenGL
	{	
	public:
		SphereObjectOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color);
		~SphereObjectOpenGL();

		SphereObjectOpenGL(const SphereObjectOpenGL& other) = delete;	// Prevent Copy Constructor
		SphereObjectOpenGL& operator=(const SphereObjectOpenGL& other) = delete;	// Prevent Copy Assignment
		SphereObjectOpenGL(SphereObjectOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
		SphereObjectOpenGL& operator=(SphereObjectOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

		// === Overrides from ILuminous ===
		bool IsLuminous() const override;
		Space::ILightBehavior* GetLightBehavior() const override;
		void SetLuminousBehavior(Space::ILightBehavior* behavior) override;

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
		unsigned int GetVertexCount() const override;
		unsigned int GetIndexCount() const override;
		const std::vector<unsigned int>& GetIndices() const override;
		const std::vector<Space::Vertex>& GetVertices() const override;

		// === Overrides from IRenderableObject ===
		Space::Color GetColor() const override;
		void SetColor(const Space::Color& color) override;

		// === Overrides from IRenderableObjectOpenGL ===
		unsigned int GetVBO() const override;
		unsigned int GetVAO() const override;
		unsigned int GetEBO() const override;

		// Getters
		float GetRadius() const;
		// Setters
		void SetRadius(float radius);

	private:
		class SphereObjectOpenGLImpl;
		SphereObjectOpenGLImpl* m_pSphereObjectOpenGLImpl;
	};
}


#endif // RENDERING__OBJECTS__SPHERE_OBJECT_OPENGL__HPP