#ifndef ENGINECORE__ENGINE_RUNNER_IMPL__HPP
#define ENGINECORE__ENGINE_RUNNER_IMPL__HPP


#include "../include/EngineRunner.hpp"
#include "../../GLFWWindow/include/GLFWWindow.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class EngineRunner::EngineRunnerImpl
		{
		public:
			EngineRunnerImpl(EngineRunner& parent);
			~EngineRunnerImpl();

			void Run();

		private:
			EngineRunner& m_parent;
			GLFWWindow m_glfwWindow;
		};
	}
}


#endif // ENGINECORE__ENGINE_RUNNER_IMPL__HPP