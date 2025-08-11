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

		void Application::AddToScene(int id, Rendering::IRenderableObjectOpenGL* object)
		{
			m_pApplicationImpl->AddToScene(id, object);
		}

		void Application::AddToScene(int id, Rendering::DirectionalLight* object)
		{
			m_pApplicationImpl->AddToScene(id, object);
		}

		void Application::RemoveFromScene(int id)
		{
			m_pApplicationImpl->RemoveFromScene(id);
		}
	}
}