#ifndef API__I_CAMERA__HPP
#define API__I_CAMERA__HPP


#include "pch.hpp"
#include "ICameraController.hpp"
#include "ICameraView.hpp"


namespace Andromeda
{
    class ICamera
        : public ICameraController
		, public ICameraView
    {
    public:
        virtual ~ICamera();
    };
}


#endif // API__I_CAMERA__HPP