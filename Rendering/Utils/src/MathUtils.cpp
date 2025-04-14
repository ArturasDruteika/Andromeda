#include "../include/MathUtils.hpp"

namespace Andromeda
{
	namespace Rendering
	{
		glm::vec2 MathUtils::ToGLM(const Math::Vec2& vec)
		{
			return glm::vec2(vec[0], vec[1]);
		}

		Math::Vec2 MathUtils::FromGLM(const glm::vec2& glmVec)
		{
			return Math::Vec2{ glmVec.x, glmVec.y };
		}

		glm::vec3 MathUtils::ToGLM(const Math::Vec3& vec)
		{
			return glm::vec3(vec[0], vec[1], vec[2]);
		}

		Math::Vec3 MathUtils::FromGLM(const glm::vec3& glmVec)
		{
			return Math::Vec3{ glmVec.x, glmVec.y, glmVec.z };
		}

		glm::vec4 MathUtils::ToGLM(const Math::Vec4& vec)
		{
			return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
		}

		Math::Vec4 MathUtils::FromGLM(const glm::vec4& glmVec)
		{
			return Math::Vec4{ glmVec.x, glmVec.y, glmVec.z, glmVec.w };
		}

		glm::mat2 MathUtils::ToGLM(const Math::Mat2& mat)
		{
			glm::mat2 glmMat;
			for (int col = 0; col < 2; ++col)
			{
				for (int row = 0; row < 2; ++row)
				{
					glmMat[col][row] = mat[col][row];
				}
			}
			return glmMat;
		}

		Math::Mat2 MathUtils::FromGLM(const glm::mat2& glmMat)
		{
			Math::Mat2 mat;
			for (int col = 0; col < 2; ++col)
			{
				for (int row = 0; row < 2; ++row)
				{
					mat[col][row] = glmMat[col][row];
				}
			}
			return mat;
		}

		glm::mat3 MathUtils::ToGLM(const Math::Mat3& mat)
		{
			glm::mat3 glmMat{};
			for (int col = 0; col < 3; ++col)
			{
				for (int row = 0; row < 3; ++row)
				{
					glmMat[col][row] = mat[col][row];
				}
			}
			return glmMat;
		}

		Math::Mat3 MathUtils::FromGLM(const glm::mat3& glmMat)
		{
			Math::Mat3 mat;
			for (int col = 0; col < 3; ++col)
			{
				for (int row = 0; row < 3; ++row)
				{
					mat[col][row] = glmMat[col][row];
				}
			}
			return mat;
		}

		glm::mat4 MathUtils::ToGLM(const Math::Mat4& mat)
		{
			glm::mat4 glmMat;
			for (int col = 0; col < 4; ++col)
			{
				for (int row = 0; row < 4; ++row)
				{
					glmMat[col][row] = mat[col][row];
				}
			}
			return glmMat;
		}

		Math::Mat4 MathUtils::FromGLM(const glm::mat4& glmMat)
		{
			Math::Mat4 mat;
			for (int col = 0; col < 4; ++col)
			{
				for (int row = 0; row < 4; ++row)
				{
					mat[col][row] = glmMat[col][row];
				}
			}
			return mat;
		}
	}
}
