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
			GridOpenGL* grid = new GridOpenGL(100, m_gridSpacing, 0.05f, Space::Color(0.3f, 0.3f, 0.3f, 1.0f));
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

		void OpenGLScene::OpenGLSceneImpl::ResizeGrid(float resizeFactor)
		{
			// Dynamically compute grid spacing based on camera distance
			float newGridSpacing = std::pow(resizeFactor, 0.9f);

			// Only update if the spacing visibly changes
			if (std::abs(newGridSpacing - m_gridSpacing) >= 0.1f)
			{
				m_gridSpacing = newGridSpacing;
				int gridIndex = static_cast<int>(SpecialIndices::Grid);
				delete m_renderableObjsPtrsMap.at(gridIndex);
				m_renderableObjsPtrsMap.erase(gridIndex);

				GridOpenGL* grid = new GridOpenGL(100, m_gridSpacing, 0.05f, Space::Color(0.3f, 0.3f, 0.3f, 1.0f));
				AddObject(gridIndex, grid);
			}
		}


		const std::unordered_map<int, IRenderableObjectOpenGL*> OpenGLScene::OpenGLSceneImpl::GetObjects() const
		{
			return m_renderableObjsPtrsMap;
		}
	}
}
