#ifndef API__ENGINE__I_ENGINE__HPP
#define API__ENGINE__I_ENGINE__HPP


#if defined(ANDROMEDA_ENGINECORE_BUILD)
	// building the DLL
	#define ANDROMEDA_ENGINE_API __declspec(dllexport)
#elif defined(ANDROMEDA_ENGINECORE_USE_DLL)
	// using the DLL
	#define ANDROMEDA_ENGINE_API __declspec(dllimport)
#else
	// static lib or no dll semantics
	#define ANDROMEDA_ENGINE_API
#endif


#include "pch.hpp"
#include "GraphicsBackend.hpp"
#include "../Renderer/IRenderer.hpp"
#include "../Scene/IScene.hpp"


namespace Andromeda
{
	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual bool IsInitialized() const = 0;
		virtual GraphicsBackend GetGraphicsBackend() const = 0;
		virtual IScene* GetScene() const = 0;
		virtual IRenderer* GetRenderer() const = 0;

		virtual bool Init() = 0;
		virtual void DeInit() = 0;
	};

	ANDROMEDA_ENGINE_API std::unique_ptr<IEngine> CreateEngine(const GraphicsBackend& graphicsBackend);
}


#endif // API__ENGINE__I_ENGINE__HPP