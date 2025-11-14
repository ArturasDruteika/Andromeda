#ifndef RENDERING__ABSTRACTS__RENDERABLE_OBJECT__HPP
#define RENDERING__ABSTRACTS__RENDERABLE_OBJECT__HPP


#include "Geometry.hpp"
#include "Luminous.hpp"
#include "Transformable.hpp"
#include "Colors.hpp"


namespace Andromeda::Rendering
{
    class RenderableObject :
        public Geometry,
        public Transformable,
        public Luminous
    {
    public:
        RenderableObject(const Math::Vec3& centerPosition, const PhysicalProperties::Color& color);
        ~RenderableObject();

        // Getters
        PhysicalProperties::Color GetColor() const;
		// Setters
		void SetColor(const PhysicalProperties::Color& color);

    protected:
        PhysicalProperties::Color m_color;

    };
}


#endif // RENDERING__ABSTRACTS__RENDERABLE_OBJECT__HPP