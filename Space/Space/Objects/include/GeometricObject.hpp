#ifndef ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP
#define ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP


#include "Andromeda/Space/Objects/IGeometricObject.hpp"
#include "Object.hpp"
#include "Transformable.hpp"
#include "Mesh.hpp"


namespace Andromeda::Space
{
	class GeometricObject
		: public virtual IGeometricObject
		, public Object
		, public Transformable
	{
	public:
		GeometricObject(const Math::Vec3& centerPosition);
		~GeometricObject();

		// Getters
		const Mesh& GetMesh() const;
		Space::Color GetColor() const;
		// Setters
		void SetColor(const Space::Color& color);

	private:
		Space::Color m_color;
		Mesh m_mesh;
	};
}


#endif // ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP