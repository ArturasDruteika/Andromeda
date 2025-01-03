#include "EngineRunnerImpl.hpp"


namespace Andromeda
{
    namespace Core
    {
        EngineRunner::EngineRunnerImpl::EngineRunnerImpl(EngineRunner& parent)
            : m_parent(parent)
        {
        }

        EngineRunner::EngineRunnerImpl::~EngineRunnerImpl()
        {
        }

        void EngineRunner::EngineRunnerImpl::Run()
        {
            m_window.RunMainLoop();
        }
    }
}

