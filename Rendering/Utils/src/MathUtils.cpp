#include "../include/MathUtils.hpp"

namespace Andromeda
{
	namespace Rendering
	{
		glm::vec2 MathUtils::ToGLM(const Vec2& vec)
		{
			return glm::vec2(vec.x, vec.y);
		}

		Vec2 MathUtils::FromGLM(const glm::vec2& glmVec)
		{
			return Vec2{ glmVec.x, glmVec.y };
		}

		glm::vec3 MathUtils::ToGLM(const Vec3& vec)
		{
			return glm::vec3(vec.x, vec.y, vec.z);
		}

		Vec3 MathUtils::FromGLM(const glm::vec3& glmVec)
		{
			return Vec3{ glmVec.x, glmVec.y, glmVec.z };
		}

		glm::vec4 MathUtils::ToGLM(const Vec4& vec)
		{
			return glm::vec4(vec.x, vec.y, vec.z, vec.w);
		}

		Vec4 MathUtils::FromGLM(const glm::vec4& glmVec)
		{
			return Vec4{ glmVec.x, glmVec.y, glmVec.z, glmVec.w };
		}

		glm::mat2 MathUtils::ToGLM(const Mat2& mat)
		{
			glm::mat2 glmMat;
			for (int col = 0; col < 2; ++col)
			{
				for (int row = 0; row < 2; ++row)
				{
					glmMat[col][row] = mat.data[col][row];
				}
			}
			return glmMat;
		}

		Mat2 MathUtils::FromGLM(const glm::mat2& glmMat)
		{
			Mat2 mat;
			for (int col = 0; col < 2; ++col)
			{
				for (int row = 0; row < 2; ++row)
				{
					mat.data[col][row] = glmMat[col][row];
				}
			}
			return mat;
		}

		glm::mat3 MathUtils::ToGLM(const Mat3& mat)
		{
			glm::mat3 glmMat;
			for (int col = 0; col < 3; ++col)
			{
				for (int row = 0; row < 3; ++row)
				{
					glmMat[col][row] = mat.data[col][row];
				}
			}
			return glmMat;
		}

		Mat3 MathUtils::FromGLM(const glm::mat3& glmMat)
		{
			Mat3 mat;
			for (int col = 0; col < 3; ++col)
			{
				for (int row = 0; row < 3; ++row)
				{
					mat.data[col][row] = glmMat[col][row];
				}
			}
			return mat;
		}

		glm::mat4 MathUtils::ToGLM(const Mat4& mat)
		{
			glm::mat4 glmMat;
			for (int col = 0; col < 4; ++col)
			{
				for (int row = 0; row < 4; ++row)
				{
					glmMat[col][row] = mat.data[col][row];
				}
			}
			return glmMat;
		}

		Mat4 MathUtils::FromGLM(const glm::mat4& glmMat)
		{
			Mat4 mat;
			for (int col = 0; col < 4; ++col)
			{
				for (int row = 0; row < 4; ++row)
				{
					mat.data[col][row] = glmMat[col][row];
				}
			}
			return mat;
		}
	}
}
