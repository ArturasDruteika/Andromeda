#include "../include/EngineRunner.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		EngineRunner::EngineRunner() = default;
		EngineRunner::~EngineRunner() = default;

		void EngineRunner::Run() 
		{
			m_glfwWindow.RunMainLoop();
		}
	}
}