#ifndef RENDERING__OBJECTS__GRID_OPENGL__HPP
#define RENDERING__OBJECTS__GRID_OPENGL__HPP


#include "../../Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "../../Abstracts/include/RenderableObjectOpenGL.hpp"
#include "Colors.hpp"


namespace Andromeda::Rendering
{
	class GridOpenGL
		: public IRenderableObjectOpenGL
		, public RenderableObjectOpenGL
	{	
	public:
		GridOpenGL(
			int gridSize = 100, 
			float spacing = 1.0f, 
			float densityFactor = 0.05, 
			const Space::Color& color = Space::Color(0.3f, 0.3f, 0.3f, 1.0f)
		);
		~GridOpenGL();

		GridOpenGL(const GridOpenGL& other) = delete;	// Prevent Copy Constructor
		GridOpenGL& operator=(const GridOpenGL& other) = delete;	// Prevent Copy Assignment
		GridOpenGL(GridOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
		GridOpenGL& operator=(GridOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

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
		int GetGridSize() const;
		float GetSpacing() const;
		float GetDensityFactor() const;
		// Setters
		void SetGridSize(int size);
		void SetSpacing(float spacing);
		void SetDensityFactor(float densityFactor);

	private:
		void ConstructGrid(int size = 100, float spacing = 1.0f, const Space::Color& gridColor = { 0.3, 0.3, 0.3, 1.0 });

	private:
		int m_gridSize;
		float m_spacing;
		float m_densityFactor;
	};
}


#endif // RENDERING__OBJECTS__GRID_OPENGL__HPP