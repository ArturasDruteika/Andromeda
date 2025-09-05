#ifndef RENDERING__CAMERA_VIEW__HPP
#define RENDERING__CAMERA_VIEW__HPP


#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class CameraView
	{
	public:
		CameraView(const glm::vec3& position, const glm::vec3& targetCoords = glm::vec3(0.0f));
		~CameraView();

		const glm::vec3& GetPosition() const;
		const glm::vec3& GetTargetCoords() const;
		const glm::vec3& GetForward() const;
		const glm::vec3& GetRight() const;
		const glm::vec3& GetUp() const;
		const glm::mat4& GetViewMatrix() const;
		// Setters
		void SetPosition(const glm::vec3& position);
		void SetTargetCoords(const glm::vec3& targetCoords);

	protected:
		void CalculateViewMatrix();

	protected:
		glm::vec3 m_position;
		glm::vec3 m_targetCoords;
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		glm::vec3 m_xAxis;
		glm::vec3 m_yAxis;
		glm::vec3 m_zAxis;
		glm::mat4 m_viewMat;
	};
}


#endif // RENDERING__CAMERA_VIEW__HPP