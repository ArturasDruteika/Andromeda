#ifndef RENDERER__I_RENDERER_OPENGL__HPP
#define RENDERER__I_RENDERER_OPENGL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "IRenderer.hpp"
#include "../include/IFrameBufferProvider.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IRendererOpenGL
		: public IRenderer
		, public IFrameBufferProvider
	{
	public:
		virtual ~IRendererOpenGL();
	};
}


#endif // RENDERER__I_RENDERER_OPENGL__HPP