#include "../include/Renderer.hpp"
#include "../include/RendererImpl.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		Renderer::Renderer()
			: m_pRendererImpl(new Renderer::RendererImpl(*this))
		{
		}

		Renderer::~Renderer()
		{
			delete m_pRendererImpl;
		}
	}
}
