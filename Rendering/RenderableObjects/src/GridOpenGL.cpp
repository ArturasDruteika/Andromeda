#include "../include/GridOpenGL.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		GridOpenGL::GridOpenGL(const Space::Color& color)
			: RenderableObjectOpenGLBase(
				Math::Vec3(0.0f, 0.0f, 0.0f),
				color,
				std::vector{
					VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 }, // Position
					VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D)}, // Color
					VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D) + sizeof(Space::Color)} // Normal
				}
			)
		{
            ConstructGrid(100, color);
            Init();
            UpdateModelMatrix(TransformationType::ALL);
		}

		GridOpenGL::~GridOpenGL() = default;

        bool GridOpenGL::IsEmitingLight() const
        {
            return RenderableObjectOpenGLBase::IsEmitingLight();
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

        void GridOpenGL::SetEmitingLight(bool isEmitingLight)
        {
            m_isEmitingLight = isEmitingLight;
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

        void GridOpenGL::ConstructGrid(int size, const Space::Color& gridColor)
        {
            m_vertices.clear();
            m_indices.clear();

            uint32_t index = 0;

            for (int i = -size; i <= size; ++i)
            {
                Space::Color color = gridColor;

                // Optional: Highlight center lines with different color
                if (i == 0)
                {
                    color = Space::Color(1.0f, 0.5f, 0.5f); // X-axis = Red
                }

                // Line parallel to Z-axis (X is constant)
                m_vertices.emplace_back(Space::Point3D((float)i, 0.0f, -size), color);
                m_vertices.emplace_back(Space::Point3D((float)i, 0.0f, size), color);
                m_indices.push_back(index++);
                m_indices.push_back(index++);

                // Line parallel to X-axis (Z is constant)
                color = (i == 0) ? Space::Color(0.5f, 0.5f, 1.0f) : gridColor; // Z-axis = Blue
                m_vertices.emplace_back(Space::Point3D(-size, 0.0f, (float)i), color);
                m_vertices.emplace_back(Space::Point3D(size, 0.0f, (float)i), color);
                m_indices.push_back(index++);
                m_indices.push_back(index++);
            }
        }
    }
}
