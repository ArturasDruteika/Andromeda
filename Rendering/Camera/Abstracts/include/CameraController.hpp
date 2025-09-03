#ifndef RENDERING__CAMERA_CONTROLLER__HPP
#define RENDERING__CAMERA_CONTROLLER__HPP


#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class CameraController
	{
	public:
		CameraController();
		~CameraController();

		void Rotate(float yaw, float pitch, float roll);
		void Zoom(float deltaDistance);

	private:
		float m_distance;
	};
}


#endif // RENDERING__CAMERA_CONTROLLER__HPP