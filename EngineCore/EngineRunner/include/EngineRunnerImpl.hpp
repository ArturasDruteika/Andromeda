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
			EngineRunnerImpl();
			~EngineRunnerImpl();

			EngineRunnerImpl(const EngineRunnerImpl& other) = delete;	// Prevent Copy Constructor
			EngineRunnerImpl& operator=(const EngineRunnerImpl& other) = delete;	// Prevent Copy assignment
			EngineRunnerImpl(EngineRunnerImpl&& other) noexcept = delete;	// Prevent Move constructor
			EngineRunnerImpl& operator=(const EngineRunnerImpl&& other) noexcept = delete;	//Prevent Move assignment

			void Run();

		private:
			GLFWWindow m_glfwWindow;
		};
	}
}


#endif // ENGINECORE__ENGINE_RUNNER_IMPL__HPP