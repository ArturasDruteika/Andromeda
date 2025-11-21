#include "IEngine.hpp"
#include "Platform.hpp"
#include "spdlog/spdlog.h"


int main(void)
{
	// 1. Init platform: window + context + GLAD
	Andromeda::Platform::Platform platform;
	if (!platform.Init(1280, 720, "Andromeda Example"))
	{
		spdlog::error("Failed to initialize Platform.");
		return -1;
	}

	std::unique_ptr<Andromeda::IEngine> pEngine = Andromeda::CreateEngine(Andromeda::GraphicsBackend::OpenGL);

	if (!pEngine)
	{
		spdlog::error("CreateEngine() returned nullptr.");
		return -1;
	}

	if (!pEngine->Init())
	{
		spdlog::error("Engine::Init() failed.");
		return -1;
	}

	Andromeda::IRenderer* pRenderer = pEngine->GetRenderer();
	Andromeda::IScene* pScene = pEngine->GetScene();

	Andromeda::IWindow* pWindow = platform.GetWindow();
	Andromeda::IGraphicsContext* pContext = platform.GetGraphicsContext();


	while (!pWindow->ShouldClose())
	{
		pWindow->PollEvents();
		pRenderer->RenderFrame(*pScene);
		pContext->Present();
	}

	platform.Shutdown();

	return 0;
}