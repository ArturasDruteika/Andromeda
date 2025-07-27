#ifndef RENDERING__I_RENDERABLE_OBJECT__HPP
#define RENDERING__I_RENDERABLE_OBJECT__HPP


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
        virtual ~IRenderableObject() = default;

        // Getters
        virtual bool StateChanged() const = 0;
        virtual Space::Color GetColor() const = 0;

        virtual void ResetState() = 0;
    };
}


#endif // RENDERING__I_RENDERABLE_OBJECT__HPP