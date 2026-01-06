#ifndef RENDERING__OPENGL__SUPPORT__MESH_CACHE__HPP__HPP
#define RENDERING__OPENGL__SUPPORT__MESH_CACHE__HPP__HPP


#include "../../Geometry/include/GpuMeshOpenGL.hpp"
#include "Andromeda/Space/Objects/IGeometricObject.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
	class MeshCacheOpenGL
	{
	public:
		MeshCacheOpenGL();
		~MeshCacheOpenGL();

		MeshCacheOpenGL(const MeshCacheOpenGL& other) = delete;
		MeshCacheOpenGL& operator=(const MeshCacheOpenGL& other) = delete;
		MeshCacheOpenGL(MeshCacheOpenGL&& other) noexcept = delete;
		MeshCacheOpenGL& operator=(MeshCacheOpenGL&& other) noexcept = delete;

		void Sync(
			const std::unordered_map<int, IGeometricObject*>& objects,
			const VertexLayout& defaultLayout
		);
		const GpuMeshOpenGL* TryGet(int objectId) const;
		void Clear();

	protected:
		std::unordered_map<int, GpuMeshOpenGL> m_meshes;
	};
}


#endif // RENDERING__OPENGL__SUPPORT__MESH_CACHE__HPP__HPP