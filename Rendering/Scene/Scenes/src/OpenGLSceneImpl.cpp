#include "../include/OpenGLSceneImpl.hpp"
#include "../../Support/include/SpecialIndices.hpp"
#include "../../../RenderableObjects/Objects/include/GridOpenGL.hpp"



namespace Andromeda::Rendering
{
	OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
		: m_gridSpacing{ 1.0f } // Default grid spacing
		, m_ambientStrength{ 0.1f } // Default ambient light strength
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

	bool OpenGLScene::OpenGLSceneImpl::StateChanged() const
	{
		for (const auto& [id, obj] : m_renderableObjsPtrsMap)
		{
			if (id >= 0)
			{
				if (obj && obj->StateChanged())
				{
					return true;
				}
			}
		}
		return false;
	}

	float OpenGLScene::OpenGLSceneImpl::GetAmbientStrength() const
	{
		return m_ambientStrength;
	}

	const std::unordered_map<int, IRenderableObjectOpenGL*>& OpenGLScene::OpenGLSceneImpl::GetObjects() const
	{
		return m_renderableObjsPtrsMap;
	}

	const std::unordered_map<int, IRenderableObjectOpenGL*>& OpenGLScene::OpenGLSceneImpl::GetLuminousObjects() const
	{
		return m_luminousObjsPtrsMap;
	}

	const std::unordered_map<int, DirectionalLight>& OpenGLScene::OpenGLSceneImpl::GetDirectionalLights() const
	{
		return m_directionalLights;
	}

	void OpenGLScene::OpenGLSceneImpl::SetAmbientStrength(float ambientStrength)
	{
		if (ambientStrength >= 0.0f && ambientStrength <= 1.0f)
		{
			m_ambientStrength = ambientStrength;
		}
		else
		{
			spdlog::warn("Ambient strength must be between 0.0 and 1.0. Value {} is ignored.", ambientStrength);
		}
	}

	void OpenGLScene::OpenGLSceneImpl::ResetState()
	{
		for (auto& [id, obj] : m_renderableObjsPtrsMap)
		{
			if (id >= 0)
			{
				obj->ResetState();
			}
		}
	}

	void OpenGLScene::OpenGLSceneImpl::AddObject(int id, IRenderableObjectOpenGL* object)
	{
		m_renderableObjsPtrsMap.insert({ id, object });
		if (object->IsLuminous())
		{
			m_luminousObjsPtrsMap.insert({ id, object });
		}
	}

	void OpenGLScene::OpenGLSceneImpl::RemoveObject(int id)
	{
		if (m_renderableObjsPtrsMap.at(id)->IsLuminous())
		{
			delete m_luminousObjsPtrsMap[id];
			m_luminousObjsPtrsMap.erase(id);
		}
		delete m_renderableObjsPtrsMap[id];
		m_renderableObjsPtrsMap.erase(id);
	}

	void OpenGLScene::OpenGLSceneImpl::AddDirectionalLight(
		int id,
		const glm::vec3& direction,
		const glm::vec3& color,
		float intensity,
		const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular
	)
	{
		m_directionalLights.insert({ id, DirectionalLight(direction, color, intensity, ambient, diffuse, specular) });
	}

	void OpenGLScene::OpenGLSceneImpl::RemoveDrectionalLight(int id)
	{
		m_directionalLights.erase(id);
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
}
