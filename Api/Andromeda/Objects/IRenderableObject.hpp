#ifndef API__OBJECTS__I_RENDERABLE_OBJECT__HPP
#define API__OBJECTS__I_RENDERABLE_OBJECT__HPP


#include "ILuminous.hpp"
#include "IMesh.hpp"
#include "IObject.hpp"
#include "ITransformable.hpp"
#include "Space/Colors/include/Colors.hpp"


namespace Andromeda
{
    class IRenderableObject 
        : public ITransformable
        , public ILuminous
        , public IMesh
        , public IObject
    {
    public:
        virtual ~IRenderableObject() = default;

        // Getters
        virtual Space::Color GetColor() const = 0;
		// Setters
        virtual void SetColor(const Space::Color& color) = 0;
    };
}


#endif // API__OBJECTS__I_RENDERABLE_OBJECT__HPP