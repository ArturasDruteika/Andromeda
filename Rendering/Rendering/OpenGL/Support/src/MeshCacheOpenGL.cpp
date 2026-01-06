#include "../include/MeshCacheOpenGL.hpp"
#include "../../../Vertices/include/VertexLayouts.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
    MeshCacheOpenGL::MeshCacheOpenGL() = default;

    MeshCacheOpenGL::~MeshCacheOpenGL() = default;

    void MeshCacheOpenGL::Sync(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const VertexLayout& defaultLayout
    )
    {
        std::unordered_set<int> objIds;
        objIds.reserve(objects.size());

        for (const auto& [sceneKey, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            const int objId = obj->GetID();
            objIds.insert(objId);

            auto it = m_meshes.find(objId);
            if (it == m_meshes.end())
            {
                GpuMeshOpenGL gpuMesh;
                gpuMesh.Create(obj->GetMesh(), defaultLayout);
                m_meshes.emplace(objId, std::move(gpuMesh));
            }
        }

        for (auto it = m_meshes.begin(); it != m_meshes.end();)
        {
            if (objIds.find(it->first) == objIds.end())
            {
                it = m_meshes.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    const GpuMeshOpenGL* MeshCacheOpenGL::TryGet(int objectId) const
    {
        auto it = m_meshes.find(objectId);
        if (it == m_meshes.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    void MeshCacheOpenGL::Clear()
    {
        m_meshes.clear();
    }
}
