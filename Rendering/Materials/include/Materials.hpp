#ifndef RENDERING__MATERIALS__HPP
#define RENDERING__MATERIALS__HPP


#include "pch.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
        enum class MaterialType 
        {
            Emerald,
            Jade,
            Obsidian,
            Pearl,
            Ruby,
            Turquoise,
            Brass,
            Bronze,
            Chrome,
            Copper,
            Gold,
            Silver,
            BlackPlastic,
            CyanPlastic,
            GreenPlastic,
            RedPlastic,
            WhitePlastic,
            YellowPlastic,
            BlackRubber,
            CyanRubber,
            GreenRubber,
            RedRubber,
            WhiteRubber,
            YellowRubber,

            Count  // always keep last; useful for iteration/arrays
        };

        struct Material 
        {
            float shininess;
            std::string name;
            Math::Vec3 ambient;
            Math::Vec3 diffuse;
            Math::Vec3 specular;
        };
	}
}


#endif // RENDERING__MATERIALS__HPP