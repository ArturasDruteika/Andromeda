#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP


#include "../../Math/include/MathTypes.hpp"
#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class Camera
		{	
		public:
			Camera();
			~Camera();

			// Getters
			glm::mat4 GetViewMatrix() const;
			glm::mat4 GetProjectionMatrix() const;

			void SetPosition(const glm::vec3& pos);
			void SetRotation(float pitch, float yaw);
			void SetProjection(float fov, float aspect, float near, float far);

		private:
			glm::mat4 m_viewMatrix;
			glm::mat4 m_projectionMatrix;
		};
	}
}


#endif // RENDERING__CAMERA__HPP