#ifndef SPACE__CAMERA__CAMERA_VIEW__HPP
#define SPACE__CAMERA__CAMERA_VIEW__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Andromeda/Space/Camera/ICameraView.hpp"


namespace Andromeda::Space
{
	class CameraView
		: public ICameraView
	{
	public:
		CameraView(const Math::Vec3& position, const Math::Vec3& targetCoords = Math::Vec3(0.0f, 0.0f, 0.0f));
		~CameraView();

		const Math::Vec3& GetPosition() const override;
		const Math::Vec3& GetTargetCoords() const override;
		const Math::Vec3& GetForward() const override;
		const Math::Vec3& GetRight() const override;
		const Math::Vec3& GetUp() const override;
		const Math::Mat4& GetViewMatrix() const override;
		// Setters
		void SetPosition(const Math::Vec3& position);
		void SetTargetCoords(const Math::Vec3& targetCoords);

	protected:
		void CalculateViewMatrix();

	protected:
		Math::Vec3 m_position;
		Math::Vec3 m_targetCoords;
		Math::Vec3 m_forward;
		Math::Vec3 m_right;
		Math::Vec3 m_up;
		Math::Mat4 m_viewMat;
	};
}


#endif // SPACE__CAMERA__CAMERA_VIEW__HPP