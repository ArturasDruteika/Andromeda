#ifndef RENDERING__CAMERA_CONTROLLER__HPP
#define RENDERING__CAMERA_CONTROLLER__HPP


#include "CameraView.hpp"
#include "PerspectiveControl.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"


namespace Andromeda::Rendering
{
	class CameraController
		: public CameraView
		, public PerspectiveControl
	{
	public:
		CameraController();
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