#ifndef SPACE__CAMERA__CAMERA_CONTROLLER__HPP
#define SPACE__CAMERA__CAMERA_CONTROLLER__HPP


#include "CameraView.hpp"
#include "Math/LinearAlgebra/include/Quaternions.hpp"
#include "Andromeda/Space/Camera/ICameraController.hpp"


namespace Andromeda::Space
{
	class CameraController
		: public CameraView
		, public virtual ICameraController
	{
	public:
		CameraController(const Math::Vec3& position, const Math::Vec3& targetCoords = Math::Vec3(0.0f, 0.0f, 0.0f));
		~CameraController();

		void Rotate(float yaw, float pitch, float roll) override;
		void Zoom(float deltaDistance) override;

		void SetOnDistanceChange(OnDistanceChange callback) override;

	private:
		void UpdateDirection();

	protected:
		float m_distance;
		Math::Quaternion m_orientation;
	};
}


#endif // SPACE__CAMERA__CAMERA_CONTROLLER__HPP