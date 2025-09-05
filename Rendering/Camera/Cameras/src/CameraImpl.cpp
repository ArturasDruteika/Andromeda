#include "../include/CameraImpl.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>

namespace Andromeda
{
    namespace Rendering
    {
        Camera::CameraImpl::CameraImpl()
            : Camera::CameraImpl(Math::Vec3(20.0f, 20.0f, 25.0f), -glm::half_pi<float>(), 0.0f)
        {
        }

        Camera::CameraImpl::CameraImpl(const Math::Vec3& position, float yawRadians, float pitchRadians)
			: PerspectiveControl(45.0f, 0.1f, 1000.0f, 1.0f)
            , CameraController(MathUtils::ToGLM(position))
        {
        }

        Camera::CameraImpl::~CameraImpl() = default;

        void Camera::CameraImpl::Zoom(float deltaDistance)
        {
			CameraController::Zoom(deltaDistance);
            m_onDistanceChangeCallback(m_distance);
        }

        void Camera::CameraImpl::SetOnDistanceChange(OnDistanceChange callback)
        {
            m_onDistanceChangeCallback = std::move(callback);
		}
    }
}
