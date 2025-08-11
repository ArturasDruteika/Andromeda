#ifndef RENDERER__I_ILLUMINATION_CONTROL__HPP
#define RENDERER__I_ILLUMINATION_CONTROL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IIlluminationControl
	{
	public:
		virtual ~IIlluminationControl();

		// Getters
		virtual bool IsIlluminationMode() const = 0;
		// Setters
		virtual void SetIlluminationMode(bool mode) = 0;
	};
}


#endif // RENDERER__I_ILLUMINATION_CONTROL__HPP