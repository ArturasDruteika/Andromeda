#ifndef API__RENDERABLE_OBJECTS__I_RENDERABLE_OBJECT__HPP
#define API__RENDERABLE_OBJECTS__I_RENDERABLE_OBJECT__HPP


#include "ILuminous.hpp"
#include "ITransformable.hpp"
#include "Colors.hpp"


namespace Andromeda
{
    class IRenderableObject :
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


#endif // API__RENDERABLE_OBJECTS__I_RENDERABLE_OBJECT__HPP