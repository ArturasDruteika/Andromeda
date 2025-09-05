#ifndef RENDERING__CAMERA_CONTROLLER__HPP
#define RENDERING__CAMERA_CONTROLLER__HPP


#include "CameraView.hpp"
#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/quaternion.hpp"


namespace Andromeda::Rendering
{
	class CameraController
		: public CameraView
	{
	public:
		CameraController(const glm::vec3& position, const glm::vec3& targetCoords = glm::vec3(0.0f));
		~CameraController();

		void Rotate(float yaw, float pitch, float roll);
		void Zoom(float deltaDistance);

	private:
		void UpdateDirection();

	protected:
		float m_distance;
		glm::quat m_orientation;
	};
}


#endif // RENDERING__CAMERA_CONTROLLER__HPP