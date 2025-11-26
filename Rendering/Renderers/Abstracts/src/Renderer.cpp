#include "../include/Renderer.hpp"


namespace Andromeda::Rendering
{
	Renderer::Renderer()
		: m_initialized{ false }
	{
	}

	Renderer::~Renderer() = default;

	bool Renderer::IsInitialized() const
	{
		return m_initialized;
	}

	void Renderer::Init(int width, int height, bool illuminationMode)
	{
	}

	void Renderer::DeInit()
	{
	}

	void Renderer::RenderFrame(IScene& scene)
	{
	}
}
