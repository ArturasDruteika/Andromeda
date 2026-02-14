#ifndef API__CAMERA__I_CAMERA__HPP
#define API__CAMERA__I_CAMERA__HPP


#include "ICameraController.hpp"
#include "ICameraView.hpp"


namespace Andromeda
{
    class ICamera
        : public virtual ICameraController
		, public virtual IPerspectiveControl
    {
    public:
        virtual ~ICamera() = default;
    };
}


#endif // API__CAMERA__I_CAMERA__HPP