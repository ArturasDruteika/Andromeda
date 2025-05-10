#ifndef RENDERING__MATH_UTLS__HPP
#define RENDERING__MATH_UTLS__HPP


#include "LinearAlgebraDataTypes.hpp"
#include <glm/glm.hpp>


namespace Andromeda
{
	namespace Rendering
	{
		class MathUtils
		{
		public:
			static glm::vec2 ToGLM(const Math::Vec2& vec);
			static Math::Vec2 FromGLM(const glm::vec2& glmVec);
			static glm::vec3 ToGLM(const Math::Vec3& vec);
			static Math::Vec3 FromGLM(const glm::vec3& glmVec);
			static glm::vec4 ToGLM(const Math::Vec4& vec);
			static Math::Vec4 FromGLM(const glm::vec4& glmVec);
			static glm::mat2 ToGLM(const Math::Mat2& mat);
			static Math::Mat2 FromGLM(const glm::mat2& glmMat);
			static glm::mat3 ToGLM(const Math::Mat3& mat);
			static Math::Mat3 FromGLM(const glm::mat3& glmMat);
			static glm::mat4 ToGLM(const Math::Mat4& mat);
			static Math::Mat4 FromGLM(const glm::mat4& glmMat);
		};
	}
}


#endif // RENDERING__MATH_UTLS__HPP