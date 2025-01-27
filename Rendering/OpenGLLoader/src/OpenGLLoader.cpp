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
			// TODO: Maybe deinit glad here?
			delete m_pOpenGLLoaderImpl;
		}

		void OpenGLLoader::LoadGlad(const char* name)
		{
			m_pOpenGLLoaderImpl->LoadGlad(name);
		}

		bool OpenGLLoader::Initialize() const
		{
			return m_pOpenGLLoaderImpl->Initialize();
		}
	}
}
