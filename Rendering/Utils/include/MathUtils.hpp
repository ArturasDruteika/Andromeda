#ifndef RENDERING__MATH_UTLS__HPP
#define RENDERING__MATH_UTLS__HPP


#include "../../Math/include/MathTypes.hpp"
#include <glm/glm.hpp>


namespace Andromeda
{
	namespace Rendering
	{
		class MathUtils
		{
		public:
			static glm::vec2 ToGLM(const Vec2& vec);
			static Vec2 FromGLM(const glm::vec2& glmVec);
			static glm::vec3 ToGLM(const Vec3& vec);
			static Vec3 FromGLM(const glm::vec3& glmVec);
			static glm::vec4 ToGLM(const Vec4& vec);
			static Vec4 FromGLM(const glm::vec4& glmVec);
			static glm::mat2 ToGLM(const Mat2& mat);
			static Mat2 FromGLM(const glm::mat2& glmMat);
			static glm::mat3 ToGLM(const Mat3& mat);
			static Mat3 FromGLM(const glm::mat3& glmMat);
			static glm::mat4 ToGLM(const Mat4& mat);
			static Mat4 FromGLM(const glm::mat4& glmMat);
		};
	}
}


#endif // RENDERING__MATH_UTLS__HPP