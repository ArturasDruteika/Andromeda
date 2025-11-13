#ifndef PHYSICAL_PROPERTIES__MATERIAL_TYPES__HPP
#define PHYSICAL_PROPERTIES__MATERIAL_TYPES__HPP


namespace Andromeda::PhysicalProperties
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


#endif // PHYSICAL_PROPERTIES__MATERIAL_TYPES__HPP