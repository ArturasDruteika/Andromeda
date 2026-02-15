#ifndef ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP
#define ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP


#include "Object.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Colors/Colors.hpp"
#include "Andromeda/Space/Objects/IGeometricObject.hpp"
#include "Mesh.hpp"


namespace Andromeda::Space
{
	class SPACE_API GeometricObject
		: public virtual IGeometricObject
		, public Object
	{
	public:
		GeometricObject();
		GeometricObject(const Color& color);
		~GeometricObject() override;

		// Getters
		const Mesh& GetMesh() const override;
		const Color& GetColor() const override;
		// Setters
		void SetMesh(const Mesh& mesh);
		void SetColor(const Color& color) override;

	protected:
		Color m_color;
		Mesh m_mesh;
	};
}


#endif // ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP