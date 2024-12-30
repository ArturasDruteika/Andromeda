#include "EngineRunnerImpl.hpp"
#include "FramebufferEvents.hpp"
#include "EventType.hpp"
#include <iostream>


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
            /*GraphicalWindow::WindowResizeEvent e(800, 600);
            if (e.IsInCategory(GraphicalWindow::EventCategory::EventCategoryApplication))
            {
                std::cout << "WindowResizeEvent: " << e.GetWidth() << ", " << e.GetHeight() << std::endl;
            }
            if (e.IsInCategory(GraphicalWindow::EventCategory::EventCategoryKeyboard))
            {
                std::cout << "WindowResizeEvent: " << e.GetWidth() << ", " << e.GetHeight() << std::endl;
            }*/
            m_window.RunMainLoop();
        }
    }
}

