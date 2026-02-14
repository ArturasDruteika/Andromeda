#include "../include/CameraHandler.hpp"
#include "../../Camera/include/Camera.hpp"


namespace Andromeda::Space
{
    CameraHandler::CameraHandler()
        : m_pCamera{ nullptr }
    {
    }

    CameraHandler::~CameraHandler()
    {
        delete m_pCamera;
        m_pCamera = nullptr;
    }

    ICamera* CameraHandler::GetActiveCamera() const
    {
        return m_pCamera;
    }

    void CameraHandler::SetActiveCamera(ICamera* camera)
    {
        if (camera == nullptr)
        {
            delete m_pCamera;
            m_pCamera = nullptr;
            return;
        }

        // Only accept Space::Camera instances.
        Camera* pNewCamera = dynamic_cast<Camera*>(camera);
        if (pNewCamera == nullptr)
        {
            // Reject unknown ICamera implementations.
            // (Keep existing camera unchanged.)
            return;
        }

        if (pNewCamera == m_pCamera)
        {
            return;
        }

        delete m_pCamera;
        m_pCamera = pNewCamera;
    }
}
