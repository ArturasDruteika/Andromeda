#ifndef RENDERING__MATERIALS_LIBRARY__HPP
#define RENDERING__MATERIALS_LIBRARY__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "Materials.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API MaterialLibrary
		{
		public:
			MaterialLibrary();
			MaterialLibrary(const std::filesystem::path& filePath);
			~MaterialLibrary();

			// Getters
			bool Has(const MaterialType& materialType) const;
			size_t GetSize() const;
			std::filesystem::path GetMaterialsConfigFilePath() const;
			std::unordered_map<MaterialType, Material> GetMaterials() const;
			Material GetMaterial(const MaterialType& materialType) const;

			bool LoadFromFile(const std::filesystem::path& filePath);
			bool SaveToFile(const std::filesystem::path& filePath) const;
			// TODO: Consider adding ability to add, remove and update materials to the config

		private:
			std::filesystem::path m_materialsConfigFilePath;
			std::unordered_map<MaterialType, Material> m_materials;
		};
	}
}


#endif // RENDERING__MATERIALS_LIBRARY__HPP