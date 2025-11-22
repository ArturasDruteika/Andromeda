#ifndef RENDERER__I_RENDERER_OPENGL__HPP
#define RENDERER__I_RENDERER_OPENGL__HPP


#include "../include/IFrameBufferProvider.hpp"
#include "../../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Renderer/IRenderer.hpp"


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