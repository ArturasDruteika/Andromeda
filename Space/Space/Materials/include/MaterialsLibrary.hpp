#ifndef SPACE__MATERIALS_LIBRARY__HPP
#define SPACE__MATERIALS_LIBRARY__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "../../Materials/include/MaterialTypes.hpp"
#include "pch.hpp"
#include "Materials.hpp"


namespace Andromeda::Space
{
	class SPACE_API MaterialLibrary
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
		std::vector<MaterialType> GetAllMaterialTypes() const;
		Material GetMaterial(const MaterialType& materialType) const;
		const Material* GetMaterialPtr(const MaterialType& materialType) const;

		bool LoadFromFile(const std::filesystem::path& filePath);
		bool SaveToFile(const std::filesystem::path& filePath) const;
		// TODO: Consider adding ability to add, remove and update materials to the config

	private:
		std::filesystem::path m_materialsConfigFilePath;
		std::unordered_map<MaterialType, Material> m_materials;
	};
}


#endif // SPACE__MATERIALS_LIBRARY__HPP