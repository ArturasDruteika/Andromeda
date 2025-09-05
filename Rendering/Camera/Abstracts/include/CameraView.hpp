#ifndef RENDERING__CAMERA_VIEW__HPP
#define RENDERING__CAMERA_VIEW__HPP


#include "LinearAlgebraDataTypes.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class CameraView
	{
	public:
		CameraView(const glm::vec3& position, const glm::vec3& targetCoords = glm::vec3(0.0f));
		~CameraView();

		Math::Vec3 GetPosition() const;
		Math::Vec3 GetTargetCoords() const;
		Math::Vec3 GetForward() const;
		Math::Vec3 GetRight() const;
		Math::Vec3 GetUp() const;
		Math::Mat4 GetViewMatrix() const;
		// Setters
		void SetPosition(const Math::Vec3& position);
		void SetTargetCoords(const Math::Vec3& targetCoords);

	protected:
		void CalculateViewMatrix();

	protected:
		glm::vec3 m_position;
		glm::vec3 m_targetCoords;
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		glm::mat4 m_viewMat;
	};
}


#endif // RENDERING__CAMERA_VIEW__HPP