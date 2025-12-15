#ifndef ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP
#define ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP


#include "Object.hpp"
#include "Andromeda/Space/Colors/Colors.hpp"
#include "Andromeda/Space/Objects/IGeometricObject.hpp"
#include "../../Transformations/include/Transformable.hpp"
#include "Mesh.hpp"


namespace Andromeda::Space
{
	class GeometricObject
		: public virtual IGeometricObject
		, public Object
		, public Transformable
	{
	public:
		GeometricObject();
		GeometricObject(const Math::Vec3& centerPosition);
		~GeometricObject() override;

		// Getters
		const Mesh& GetMesh() const override;
		Color GetColor() const override;
		// Setters
		void SetColor(const Color& color) override;

	private:
		Color m_color;
		Mesh m_mesh;
	};
}


#endif // ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP