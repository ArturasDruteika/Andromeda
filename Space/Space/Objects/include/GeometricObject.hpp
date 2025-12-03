#ifndef RENDERING__ABSTRACTS__RENDERABLE_OBJECT__HPP
#define RENDERING__ABSTRACTS__RENDERABLE_OBJECT__HPP


#include "Mesh.hpp"
#include "Luminous.hpp"
#include "Transformable.hpp"
#include "Space/Colors/include/Colors.hpp"


namespace Andromeda::Space
{
    class RenderableObject :
        public Mesh,
        public Transformable,
        public Luminous
    {
    public:
        RenderableObject(const Math::Vec3& centerPosition, const Space::Color& color);
        ~RenderableObject();

        // Getters
        Space::Color GetColor() const;
		// Setters
		void SetColor(const Space::Color& color);

    protected:
        Space::Color m_color;

    };
}


#endif // RENDERING__ABSTRACTS__RENDERABLE_OBJECT__HPP