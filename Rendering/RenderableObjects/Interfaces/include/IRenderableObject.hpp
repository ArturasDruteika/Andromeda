#ifndef RENDERING__INTERFACES__I_RENDERABLE_OBJECT__HPP
#define RENDERING__INTERFACES__I_RENDERABLE_OBJECT__HPP


#if defined(_WIN32)
    #if defined(RENDERING_EXPORT)
        #define RENDERING_API __declspec(dllexport)
    #else
        #define RENDERING_API __declspec(dllimport)
    #endif /* RENDERING_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define RENDERING_API __attribute__((visibility("default")))
#endif


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
        virtual Space::Color GetColor() const = 0;
		// Setters
        virtual void SetColor(const Space::Color& color) = 0;
    };
}


#endif // RENDERING__INTERFACES__I_RENDERABLE_OBJECT__HPP