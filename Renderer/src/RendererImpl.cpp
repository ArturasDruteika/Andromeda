#include "../include/RendererImpl.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		Renderer::RendererImpl::RendererImpl(Renderer& parent)
			: m_parent(parent)
		{
		}

		Renderer::RendererImpl::~RendererImpl()
		{
		}
	}
}
