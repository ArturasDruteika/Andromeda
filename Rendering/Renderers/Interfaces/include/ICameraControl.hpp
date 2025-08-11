#ifndef RENDERER__I_CAMERA_CONTROL__HPP
#define RENDERER__I_CAMERA_CONTROL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../../Camera/include/ICamera.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ICameraControl
	{
	public:
		virtual ~ICameraControl();

		// Setters
		virtual void SetCamera(ICamera* camera) = 0;
	};
}


#endif // RENDERER__I_CAMERA_CONTROL__HPP