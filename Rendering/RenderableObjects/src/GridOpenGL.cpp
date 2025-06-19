#include "../include/GridOpenGL.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		GridOpenGL::GridOpenGL(int gridSize, float spacing, float densityFactor, const Space::Color& color)
			: m_gridSize{ gridSize }
            , m_spacing{ spacing }
            , m_densityFactor{ densityFactor }
            , RenderableObjectOpenGLBase(
				Math::Vec3(0.0f, 0.0f, 0.0f),
				color,
				std::vector{
					VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 }, // Position
					VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D)}, // Color
					VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D) + sizeof(Space::Color)} // Normal
				}
			)
		{
            ConstructGrid(100, spacing, color);
            Init();
            UpdateModelMatrix(TransformationType::ALL);
		}

		GridOpenGL::~GridOpenGL() = default;

        bool GridOpenGL::IsLuminous() const
        {
            return RenderableObjectOpenGLBase::IsLuminous();
        }

        unsigned int GridOpenGL::GetVBO() const
        {
            return RenderableObjectOpenGLBase::GetVBO();
        }

        unsigned int GridOpenGL::GetVAO() const
        {
            return RenderableObjectOpenGLBase::GetVAO();
        }

        unsigned int GridOpenGL::GetEBO() const
        {
            return RenderableObjectOpenGLBase::GetEBO();
        }

        unsigned int GridOpenGL::GetVertexCount() const
        {
            return m_vertices.size();
        }

        unsigned int GridOpenGL::GetIndicesCount() const
        {
            return m_indices.size();
        }

        std::vector<Vertex> GridOpenGL::GetVertices() const
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

        Space::Color GridOpenGL::GetColor() const
        {
            return m_color;
        }

        ILightBehavior* GridOpenGL::GetLightBehavior() const
        {
            return nullptr;
        }

        void GridOpenGL::SetLuminous(bool isEmitingLight)
        {
            m_luminous = isEmitingLight;
        }

        void GridOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
        {
            m_modelMatrix = MathUtils::ToGLM(modelMatrix);
        }

        void GridOpenGL::Translate(const Math::Vec3& translation)
        {
            RenderableObjectOpenGLBase::Translate(translation);
        }

        void GridOpenGL::TranslateDelta(const Math::Vec3& translationDelta)
        {
            RenderableObjectOpenGLBase::TranslateDelta(translationDelta);
        }

        void GridOpenGL::Rotate(const Math::Vec3& rotation)
        {
            RenderableObjectOpenGLBase::Rotate(rotation);
        }

        void GridOpenGL::RotateX(float angle)
        {
            RenderableObjectOpenGLBase::RotateX(angle);
        }

        void GridOpenGL::RotateY(float angle)
        {
            RenderableObjectOpenGLBase::RotateY(angle);
        }

        void GridOpenGL::RotateZ(float angle)
        {
            RenderableObjectOpenGLBase::RotateZ(angle);
        }

        void GridOpenGL::Scale(const Math::Vec3& scale)
        {
            RenderableObjectOpenGLBase::Scale(scale);
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
			UpdateModelMatrix(TransformationType::ALL);
        }

        void GridOpenGL::SetSpacing(float spacing)
        {
			m_spacing = spacing;
			ConstructGrid(100, spacing, m_color); // Reconstruct grid with new spacing
			UpdateModelMatrix(TransformationType::ALL);
        }

        void GridOpenGL::SetDensityFactor(float densityFactor)
        {
			m_densityFactor = densityFactor;
			ConstructGrid(100, m_spacing, m_color); // Reconstruct grid with new density factor
			UpdateModelMatrix(TransformationType::ALL);
        }

        void GridOpenGL::ConstructGrid(int size, float spacing, const Space::Color& gridColor)
        {
            m_vertices.clear();
            m_indices.clear();

            uint32_t index = 0;
            float scaledSpacing = spacing * m_densityFactor;
            float max = static_cast<float>(size);

            for (float i = -max; i <= max; i += m_densityFactor)
            {
                float coord = i * spacing;
                Space::Color color = gridColor;

                if (std::abs(i) < 0.001f) // Center line
                {
                    color = Space::Color(1.0f, 0.5f, 0.5f); // X-axis = Red
                }

                // Line parallel to Z-axis (X is constant)
                m_vertices.emplace_back(Space::Point3D(coord, 0.0f, -size * spacing), color);
                m_vertices.emplace_back(Space::Point3D(coord, 0.0f, size * spacing), color);
                m_indices.push_back(index++);
                m_indices.push_back(index++);

                // Line parallel to X-axis (Z is constant)
                color = (std::abs(i) < 0.001f) ? Space::Color(0.5f, 0.5f, 1.0f) : gridColor; // Z-axis = Blue
                m_vertices.emplace_back(Space::Point3D(-size * spacing, 0.0f, coord), color);
                m_vertices.emplace_back(Space::Point3D(size * spacing, 0.0f, coord), color);
                m_indices.push_back(index++);
                m_indices.push_back(index++);
            }
        }

    }
}
