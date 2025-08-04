#ifndef RENDERER__RENDERER_OPENGL__HPP
#define RENDERER__RENDERER_OPENGL__HPP


#include "../include/Renderer.hpp"


namespace Andromeda::Rendering
{
	class RendererOpenGL
		: public Renderer
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();
	};
}


#endif // RENDERER__RENDERER_OPENGL__HPP