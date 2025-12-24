#ifndef ENGINECORE__ENGINE__HPP
#define ENGINECORE__ENGINE__HPP

#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Components/GraphicsBackend.hpp"
#include "Andromeda/Engine/IEngine.hpp"


namespace Andromeda::EngineCore
{
	class ENGINECORE_API Engine
		: public IEngine
	{
	public:
		Engine(const GraphicsBackend& graphicsBackend);
		~Engine() override;

		bool IsInitialized() const override;
		GraphicsBackend GetGraphicsBackend() const override;
		IRenderer* GetRenderer() const override;

		bool Init() override;
		void DeInit() override;

		void OnEvent(IEvent& event) override;

	private:
		void CreateRenderer();
		void DestroyRenderer();

	private:
		bool m_initialized;
		GraphicsBackend m_graphicsBackend;
		std::unique_ptr<IRenderer> m_renderer;
	};
}


#endif // ENGINECORE__ENGINE__HPP