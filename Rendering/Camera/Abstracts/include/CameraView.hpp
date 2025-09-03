#ifndef RENDERING__CAMERA_VIEW__HPP
#define RENDERING__CAMERA_VIEW__HPP


#include "glm/glm.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
	class CameraView
	{
	public:
		CameraView();
		~CameraView();

		Math::Mat4 GetViewMatrix() const;
		Math::Vec3 GetPosition() const;
		Math::Vec3 GetForward() const;
		Math::Vec3 GetRight() const;
		Math::Vec3 GetUp() const;

	private:
		float m_fovDeg;
		float m_nearPlane;
		float m_farPlane;
		float m_aspect;
		glm::mat4 m_projection;
	};
}


#endif // RENDERING__CAMERA_VIEW__HPP