#ifndef CORE__ENGINE_RUNNER_IMPL__HPP
#define CORE__ENGINE_RUNNER_IMPL__HPP


#include "EngineRunner.hpp"
#include "GLFWWindow.hpp"


namespace Andromeda
{
	namespace Core
	{
		class EngineRunner::EngineRunnerImpl
		{
		public:
			EngineRunnerImpl(EngineRunner& parent);
			~EngineRunnerImpl();

			void Run();

		private:
			EngineRunner& m_parent;
			Andromeda::GraphicalWindow::GLFWWindow m_window;
		};
	}
}


#endif // CORE__ENGINE_RUNNER_IMPL__HPP