#include "../include/OpenGLRendererImpl.hpp"
#include "FileOperations.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
			: m_isInitialized{ false }
            , m_shader{ nullptr }
		{
		}

		OpenGLRenderer::OpenGLRendererImpl::~OpenGLRendererImpl()
		{
            if (m_shader != nullptr)
            {
                delete m_shader;
            }
		}

        bool OpenGLRenderer::OpenGLRendererImpl::IsInitialized() const
        {
            return m_isInitialized;
        }

		void OpenGLRenderer::OpenGLRendererImpl::Initialize(const char* name)
		{
            LoadGlad(reinterpret_cast<GLADloadfunc>(name));

            // Initialize OpenGL-specific states
            // TODO: Uncomment it when 3D stuff begins
            //glEnable(GL_DEPTH_TEST);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            CreateShader();
            m_isInitialized = true;
		}

		void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(const Environment::OpenGLScene& scene)
		{
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(m_shader->GetProgram());
            for (const auto& [id, object] : scene.GetObjects())
            {
                glBindVertexArray(object->GetVAO());
                glDrawArrays(GL_TRIANGLES, 0, object->GetVertexCount());
            }
		}

		void OpenGLRenderer::OpenGLRendererImpl::Shutdown()
		{
            // Cleanup resources
            delete m_shader;
            m_shader = nullptr;
            //glDeleteBuffers(1, &m_VBO);
            //glDeleteVertexArrays(1, &m_VAO);
			m_isInitialized = false;
		}

        void OpenGLRenderer::OpenGLRendererImpl::LoadGlad(GLADloadfunc load)
        {
            if (!gladLoadGL(load))
            {
                spdlog::error("Failed to initialize GLAD.");
                return;
            }
            const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            spdlog::info("GLAD initialized successfully. OpenGL version: {}", std::string(version));
        }

        void OpenGLRenderer::OpenGLRendererImpl::CreateShader()
        {
            std::string vertexShaderSource = Utils::FileOperations::LoadFileAsString("shader_program_sources/vertex_shader.glsl");
            std::string fragmentShaderSource = Utils::FileOperations::LoadFileAsString("shader_program_sources/fragment_shader.glsl");
            m_shader = new OpenGLShader(vertexShaderSource, fragmentShaderSource);
        }
	}
}
