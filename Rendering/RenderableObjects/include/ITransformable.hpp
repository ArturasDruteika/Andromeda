#ifndef RENDERING__I_TRANSFORMABLE__HPP
#define RENDERING__I_TRANSFORMABLE__HPP


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


#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ITransformable
    {
    public:
        virtual ~ITransformable();

		// Getters
		virtual Math::Vec3 GetCenterPosition() const = 0;
        virtual Math::Mat4 GetModelMatrix() const = 0;
		// Setters
        virtual void SetModelMatrix(const Math::Mat4& modelMatrix) = 0;

        virtual void Translate(const Math::Vec3& translation) = 0;
        virtual void TranslateDelta(const Math::Vec3& translationDelta) = 0;
        virtual void Rotate(const Math::Vec3& rotation) = 0;
        virtual void RotateX(float angle) = 0;
        virtual void RotateY(float angle) = 0;
        virtual void RotateZ(float angle) = 0;
        virtual void Scale(const Math::Vec3& scale) = 0;
    };
}


#endif // RENDERING__I_TRANSFORMABLE__HPP