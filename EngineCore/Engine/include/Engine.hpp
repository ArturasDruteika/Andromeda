#ifndef ENGINECORE__ENGINE__HPP
#define ENGINECORE__ENGINE__HPP

#include "../../MacroExports/include/MacroExports.hpp"
#include "IEngine.hpp"


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
		IScene* GetScene() const override;
		IRenderer* GetRenderer() const override;

		bool Init() override;
		void DeInit() override;

	private:
		void CreateRenderer();
		void CreateScene();

		void DestroyRenderer();
		void DestroyScene();

	private:
		bool m_initialized;
		GraphicsBackend m_graphicsBackend;

		std::unique_ptr<IRenderer> m_renderer;
		std::unique_ptr<IScene> m_scene;
	};

}


#endif // ENGINECORE__ENGINE__HPP