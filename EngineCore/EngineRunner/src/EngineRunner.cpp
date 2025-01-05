#include "../include/EngineRunner.hpp"
#include "../include/EngineRunnerImpl.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		EngineRunner::EngineRunner()
			: m_pEngineRunnerImpl{ new EngineRunner::EngineRunnerImpl(*this) }
		{
		}

		EngineRunner::~EngineRunner() = default;

		void EngineRunner::Run() 
		{
			m_pEngineRunnerImpl->Run();
		}
	}
}