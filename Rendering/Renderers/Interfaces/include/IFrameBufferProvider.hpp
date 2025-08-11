#ifndef RENDERER__I_FRAMEBUFFER_PROVIDER__HPP
#define RENDERER__I_FRAMEBUFFER_PROVIDER__HPP


#include "../../../MacroExports/include/MacroExports.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IFrameBufferProvider
	{
	public:
		virtual ~IFrameBufferProvider();

		// Getters
		virtual unsigned int GetFrameBufferTexture() const = 0;
	};
}


#endif // RENDERER__I_FRAMEBUFFER_PROVIDER__HPP