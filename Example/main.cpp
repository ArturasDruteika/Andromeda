#include "Engine/IEngine.hpp"
#include "Platform/IPlatform.hpp"
#include "spdlog/spdlog.h"


int main(void)
{
	unsigned int width = 800;
	unsigned int height = 600;
	std::string title = "Andromeda";

	std::unique_ptr<Andromeda::IPlatform> pPlatform = Andromeda::CreatePlatform(Andromeda::GraphicsBackend::OpenGL);
	if (!pPlatform->Init(width, height, title))
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

	Andromeda::IWindow* pWindow = pPlatform->GetWindow();
	Andromeda::IGraphicsContext* pContext = pPlatform->GetGraphicsContext();


	while (!pWindow->ShouldClose())
	{
		pWindow->PollEvents();
		pRenderer->RenderFrame(*pScene);
		pContext->Present();
	}

	pPlatform->Shutdown();

	return 0;
}