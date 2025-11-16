#include "../include/GridOpenGL.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"


namespace Andromeda::Rendering
{
    GridOpenGL::GridOpenGL(int gridSize, float spacing, float densityFactor, const PhysicalProperties::Color& color)
		: m_gridSize{ gridSize }
        , m_spacing{ spacing }
        , m_densityFactor{ densityFactor }
        , RenderableObjectOpenGL(
			Math::Vec3(0.0f, 0.0f, 0.0f),
			color,
			std::vector{
				VertexAttributes{ 0, PhysicalProperties::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(PhysicalProperties::Vertex), 0 }, // Position
				VertexAttributes{ 1, PhysicalProperties::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(PhysicalProperties::Vertex), sizeof(PhysicalProperties::Point3D)}, // Color
				VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(PhysicalProperties::Vertex), sizeof(PhysicalProperties::Point3D) + sizeof(PhysicalProperties::Color)} // Normal
			}
		)
	{
        ConstructGrid(100, spacing, color);
        Init();
        RenderableObject::UpdateModelMatrix(PhysicalProperties::TransformationType::ALL);
	}

	GridOpenGL::~GridOpenGL() = default;

    bool GridOpenGL::IsLuminous() const
    {
        return RenderableObject::IsLuminous();
    }

    bool GridOpenGL::StateChanged() const
    {
        return RenderableObjectOpenGL::StateChanged();
    }

    unsigned int GridOpenGL::GetVBO() const
    {
        return RenderableObjectOpenGL::GetVBO();
    }

    unsigned int GridOpenGL::GetVAO() const
    {
        return RenderableObjectOpenGL::GetVAO();
    }

    unsigned int GridOpenGL::GetEBO() const
    {
        return RenderableObjectOpenGL::GetEBO();
    }

    unsigned int GridOpenGL::GetVertexCount() const
    {
        return m_vertices.size();
    }

    unsigned int GridOpenGL::GetIndexCount() const
    {
        return m_indices.size();
    }

    const std::vector<unsigned int>& GridOpenGL::GetIndices() const
    {
        return m_indices;
    }

    const std::vector<PhysicalProperties::Vertex>& GridOpenGL::GetVertices() const
    {
        return m_vertices;
    }

    Math::Vec3 GridOpenGL::GetCenterPosition() const
    {
        return MathUtils::FromGLM(m_centerPosition);
    }

    Math::Mat4 GridOpenGL::GetModelMatrix() const
    {
        return MathUtils::FromGLM(m_modelMatrix);
    }

    PhysicalProperties::Color GridOpenGL::GetColor() const
    {
        return m_color;
    }

    PhysicalProperties::ILightBehavior* GridOpenGL::GetLightBehavior() const
    {
        return nullptr;
    }

    void GridOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
    {
        m_modelMatrix = MathUtils::ToGLM(modelMatrix);
    }

    void GridOpenGL::SetLuminousBehavior(PhysicalProperties::ILightBehavior* behavior)
    {
		// This object does not support luminous behavior, so we do nothing.
    }

    void GridOpenGL::ResetState()
    {
        // This is not needed for this class
    }

    void GridOpenGL::Translate(const Math::Vec3& translation)
    {
        RenderableObjectOpenGL::Translate(translation);
    }

    void GridOpenGL::TranslateDelta(const Math::Vec3& translationDelta)
    {
        RenderableObjectOpenGL::TranslateDelta(translationDelta);
    }

    void GridOpenGL::Rotate(const Math::Vec3& rotation)
    {
        RenderableObjectOpenGL::Rotate(rotation);
    }

    void GridOpenGL::RotateX(float angle)
    {
        RenderableObjectOpenGL::RotateX(angle);
    }

    void GridOpenGL::RotateY(float angle)
    {
        RenderableObjectOpenGL::RotateY(angle);
    }

    void GridOpenGL::RotateZ(float angle)
    {
        RenderableObjectOpenGL::RotateZ(angle);
    }

    void GridOpenGL::Scale(const Math::Vec3& scale)
    {
        RenderableObjectOpenGL::Scale(scale);
    }

    void GridOpenGL::SetColor(const PhysicalProperties::Color& color)
    {
    }

    int GridOpenGL::GetGridSize() const
    {
        return m_gridSize;
    }

    float GridOpenGL::GetSpacing() const
    {
        return m_spacing;
    }

    float GridOpenGL::GetDensityFactor() const
    {
        return m_densityFactor;
    }

    void GridOpenGL::SetGridSize(int size)
    {
		m_gridSize = size;
		ConstructGrid(size, m_spacing, m_color); // Reconstruct grid with new size
        RenderableObjectOpenGL::UpdateModelMatrix(PhysicalProperties::TransformationType::ALL);
    }

    void GridOpenGL::SetSpacing(float spacing)
    {
		m_spacing = spacing;
		ConstructGrid(100, spacing, m_color); // Reconstruct grid with new spacing
        UpdateModelMatrix(PhysicalProperties::TransformationType::ALL);
    }

    void GridOpenGL::SetDensityFactor(float densityFactor)
    {
		m_densityFactor = densityFactor;
		ConstructGrid(100, m_spacing, m_color); // Reconstruct grid with new density factor
        UpdateModelMatrix(PhysicalProperties::TransformationType::ALL);
    }

    void GridOpenGL::ConstructGrid(int size, float spacing, const PhysicalProperties::Color& gridColor)
    {
        m_vertices.clear();
        m_indices.clear();

        uint32_t index = 0;
        float scaledSpacing = spacing * m_densityFactor;
        float max = static_cast<float>(size);

        for (float i = -max; i <= max; i += m_densityFactor)
        {
            float coord = i * spacing;
            PhysicalProperties::Color color = gridColor;

            if (std::abs(i) < 0.001f) // Center line
            {
                color = PhysicalProperties::Color(1.0f, 0.5f, 0.5f); // X-axis = Red
            }

            // Line parallel to Z-axis (X is constant)
            m_vertices.emplace_back(PhysicalProperties::Point3D(coord, 0.0f, -size * spacing), color);
            m_vertices.emplace_back(PhysicalProperties::Point3D(coord, 0.0f, size * spacing), color);
            m_indices.push_back(index++);
            m_indices.push_back(index++);

            // Line parallel to X-axis (Z is constant)
            color = (std::abs(i) < 0.001f) ? PhysicalProperties::Color(0.5f, 0.5f, 1.0f) : gridColor; // Z-axis = Blue
            m_vertices.emplace_back(PhysicalProperties::Point3D(-size * spacing, 0.0f, coord), color);
            m_vertices.emplace_back(PhysicalProperties::Point3D(size * spacing, 0.0f, coord), color);
            m_indices.push_back(index++);
            m_indices.push_back(index++);
        }
    }
}
