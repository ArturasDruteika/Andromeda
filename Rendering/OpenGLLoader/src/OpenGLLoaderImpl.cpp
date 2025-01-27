#include "../include/OpenGLLoaderImpl.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLLoader::OpenGLLoaderImpl::OpenGLLoaderImpl()
			: m_isInitialized{ false }
		{
		}

		OpenGLLoader::OpenGLLoaderImpl::~OpenGLLoaderImpl()
		{
		}

		void OpenGLLoader::OpenGLLoaderImpl::LoadGlad(const char* name)
		{

			if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(name)))
			{
				spdlog::error("Failed to initialize GLAD.");
				m_isInitialized = false;
				return;
			}
			const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
			spdlog::info("GLAD initialized successfully. OpenGL version: {}", std::string(version));
			m_isInitialized = true;
		}

		bool OpenGLLoader::OpenGLLoaderImpl::IsInitialized() const
		{
			return m_isInitialized;
		}
	}
}
