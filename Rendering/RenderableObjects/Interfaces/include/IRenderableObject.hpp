#ifndef RENDERING__INTERFACES__I_RENDERABLE_OBJECT__HPP
#define RENDERING__INTERFACES__I_RENDERABLE_OBJECT__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "IGeometry.hpp"
#include "ILuminous.hpp"
#include "ITransformable.hpp"
#include "Colors.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API IRenderableObject :
        public IGeometry,
        public ITransformable,
        public ILuminous
    {
    public:
        virtual ~IRenderableObject();

        // Getters
        virtual PhysicalProperties::Color GetColor() const = 0;
		// Setters
        virtual void SetColor(const PhysicalProperties::Color& color) = 0;
    };
}


#endif // RENDERING__INTERFACES__I_RENDERABLE_OBJECT__HPP