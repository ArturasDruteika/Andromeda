#include "../include/EngineRunnerImpl.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		EngineRunner::EngineRunnerImpl::EngineRunnerImpl()
		{
		}

		EngineRunner::EngineRunnerImpl::~EngineRunnerImpl() = default;

		void EngineRunner::EngineRunnerImpl::Run()
		{
			m_glfwWindow.RunMainLoop();
			m_glfwWindow.DeInit();
		}
	}
}