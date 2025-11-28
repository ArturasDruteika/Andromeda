#ifndef API__OBJECTS__I_GEOMETRIC_OBJECT__HPP
#define API__OBJECTS__I_GEOMETRIC_OBJECT__HPP


#include "IObject.hpp"
#include "ITransformable.hpp"
#include "IMesh.hpp"


namespace Andromeda
{
	class IGeometricObject
        : public IObject
        , public ITransformable
	{
	public:
		virtual ~IGeometricObject() = default;
		
		// Getters
        virtual const IMesh& GetMesh() const = 0;
		virtual Space::Color GetColor() const = 0;
		// Setters
        virtual void SetColor(const Space::Color& color) = 0;
	};
}


#endif // API__OBJECTS__I_GEOMETRIC_OBJECT__HPP