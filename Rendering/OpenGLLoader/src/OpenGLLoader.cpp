#include "../include/OpenGLLoader.hpp"
#include "../include/OpenGLLoaderImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLLoader::OpenGLLoader()
			: m_pOpenGLLoaderImpl{ new OpenGLLoader::OpenGLLoaderImpl() }
		{
		}

		OpenGLLoader::~OpenGLLoader()
		{
			delete m_pOpenGLLoaderImpl;
		}

		void OpenGLLoader::LoadGlad(const char* name)
		{
			m_pOpenGLLoaderImpl->LoadGlad(name);
		}

		bool OpenGLLoader::IsInitialized() const
		{
			return m_pOpenGLLoaderImpl->IsInitialized();
		}
	}
}
