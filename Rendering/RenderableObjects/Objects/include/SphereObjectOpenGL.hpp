#ifndef RENDERING__OBJECTS__SPHERE_OBJECT_OPENGL__HPP
#define RENDERING__OBJECTS__SPHERE_OBJECT_OPENGL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "Colors.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API SphereObjectOpenGL
		: public IRenderableObjectOpenGL
	{	
	public:
		SphereObjectOpenGL(const Math::Vec3& centerPosition, float radius, const PhysicalProperties::Color& color);
		~SphereObjectOpenGL();

		SphereObjectOpenGL(const SphereObjectOpenGL& other) = delete;	// Prevent Copy Constructor
		SphereObjectOpenGL& operator=(const SphereObjectOpenGL& other) = delete;	// Prevent Copy Assignment
		SphereObjectOpenGL(SphereObjectOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
		SphereObjectOpenGL& operator=(SphereObjectOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

		// === Overrides from ILuminous ===
		bool IsLuminous() const override;
		PhysicalProperties::ILightBehavior* GetLightBehavior() const override;
		void SetLuminousBehavior(PhysicalProperties::ILightBehavior* behavior) override;

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
		std::vector<PhysicalProperties::Vertex> GetVertices() const override;

		// === Overrides from IRenderableObject ===
		PhysicalProperties::Color GetColor() const override;
		void SetColor(const PhysicalProperties::Color& color) override;

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