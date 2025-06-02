#include "../include/OpenGLSceneImpl.hpp"
#include "../include/SpecialIndices.hpp"
#include "../../RenderableObjects/include/GridOpenGL.hpp"



namespace Andromeda
{
	namespace Rendering
	{
		OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
			: m_gridSpacing{ 1.0f } // Default grid spacing
		{
			GridOpenGL* grid = new GridOpenGL(m_gridSpacing, Space::Color(0.3f, 0.3f, 0.3f, 1.0f));
			AddObject(static_cast<int>(SpecialIndices::Grid), grid);
		}

		OpenGLScene::OpenGLSceneImpl::~OpenGLSceneImpl()
		{
			for (auto& [id, obj] : m_renderableObjsPtrsMap)
			{
				delete obj;
				m_renderableObjsPtrsMap.at(id) = nullptr;
			}
			m_renderableObjsPtrsMap.clear();
		}

		void OpenGLScene::OpenGLSceneImpl::AddObject(int id, IRenderableObjectOpenGL* object)
		{
			m_renderableObjsPtrsMap.insert({ id, object });
		}

		void OpenGLScene::OpenGLSceneImpl::RemoveObject(int id)
		{
			delete m_renderableObjsPtrsMap[id];
			m_renderableObjsPtrsMap.erase(id);
		}

		void OpenGLScene::OpenGLSceneImpl::ResizeGrid(bool increase)
		{
			// Use exponential scaling factor (match the zoom style)
			float scaleFactor = std::exp((increase ? 1.0f : -1.0f) * 0.1f); // 0.1f = smoothing factor
			m_gridSpacing *= scaleFactor;

			// Optional: clamp to avoid going too small or too large
			m_gridSpacing = std::clamp(m_gridSpacing, 2.0f, 200.0f);
			delete m_renderableObjsPtrsMap.at(static_cast<int>(SpecialIndices::Grid));
			m_renderableObjsPtrsMap.erase(static_cast<int>(SpecialIndices::Grid));
			GridOpenGL* grid = new GridOpenGL(m_gridSpacing, Space::Color(0.3f, 0.3f, 0.3f, 1.0f));
			AddObject(static_cast<int>(SpecialIndices::Grid), grid);
		}

		const std::unordered_map<int, IRenderableObjectOpenGL*> OpenGLScene::OpenGLSceneImpl::GetObjects() const
		{
			return m_renderableObjsPtrsMap;
		}
	}
}
