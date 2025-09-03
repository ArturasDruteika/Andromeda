#ifndef RENDERING__I_CAMERA__HPP
#define RENDERING__I_CAMERA__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "ICameraController.hpp"
#include "ICameraView.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ICamera
        : public ICameraController
		, public ICameraView
    {
    public:
        virtual ~ICamera();
    };
}


#endif // RENDERING__I_CAMERA__HPP