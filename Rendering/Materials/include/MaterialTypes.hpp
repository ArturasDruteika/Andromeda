#ifndef RENDERING__MATERIAL_TYPES__HPP
#define RENDERING__MATERIAL_TYPES__HPP


namespace Andromeda
{
	namespace Rendering
	{
        enum class MaterialType 
        {
            None,

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
	}
}


#endif // RENDERING__MATERIAL_TYPES__HPP