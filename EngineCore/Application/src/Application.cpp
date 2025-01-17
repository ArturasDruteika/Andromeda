#include "../include/Application.hpp"
#include "../include/ApplicationImpl.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		Application::Application()
			: m_pApplicationImpl{ new Application::ApplicationImpl() }
		{
		}

		Application::~Application() = default;

		void Application::Init()
		{
			m_pApplicationImpl->Init();
		}

		void Application::RunMainLoop()
		{
			m_pApplicationImpl->RunMainLoop();
		}

		void Application::DeInit()
		{
			m_pApplicationImpl->DeInit();
		}
	}
}