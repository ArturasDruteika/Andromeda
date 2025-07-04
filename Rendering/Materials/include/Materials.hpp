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
            float shininess = 0.0f;
            std::string name = "None";
            Math::Vec3 ambient = { 0.0f, 0.0f, 0.0f };
            Math::Vec3 diffuse = { 0.0f, 0.0f, 0.0f };
            Math::Vec3 specular = { 0.0f, 0.0f, 0.0f };
        };
	}
}


#endif // RENDERING__MATERIALS__HPP