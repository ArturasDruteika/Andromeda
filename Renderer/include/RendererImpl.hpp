#ifndef RENDERER__RENDERER_IMPL__HPP
#define RENDERER__RENDERER_IMPL__HPP


#include "Renderer.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		class Renderer::RendererImpl
		{
		public:
			RendererImpl(Renderer& parent);
			~RendererImpl();

		private:
			Renderer& m_parent;
		};
	}
}


#endif // RENDERER__RENDERER_IMPL__HPP