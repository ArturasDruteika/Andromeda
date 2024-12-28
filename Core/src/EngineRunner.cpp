#include "EngineRunner.hpp"
#include "EngineRunnerImpl.hpp"


namespace Core
{
    EngineRunner::EngineRunner()
		: m_pEngineRunnerImpl(new EngineRunner::EngineRunnerImpl(*this))
    {
    }

    EngineRunner::~EngineRunner()
    {
    }

    void EngineRunner::Run()
    {
        m_pEngineRunnerImpl->Run();
    }

}
