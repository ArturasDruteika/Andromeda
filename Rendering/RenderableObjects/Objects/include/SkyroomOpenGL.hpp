#ifndef RENDERING__OBJECTS__SKYROOM_OPENGL__HPP
#define RENDERING__OBJECTS__SKYROOM_OPENGL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../Interfaces/include/IRenderableObjectOpenGL.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API SkyroomOpenGL
		: public IRenderableObjectOpenGL
	{
		public:
		SkyroomOpenGL(const Math::Vec3& centerPosition, float halfExtent, const Space::Color& color);
		~SkyroomOpenGL() override;

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

	private:
		class SkyroomOpenGLImpl;
		SkyroomOpenGLImpl* m_pSkyroomOpenGLImpl;
	};
}


#endif // RENDERING__OBJECTS__SKYROOM_OPENGL__HPP