#ifndef RENDERING__MATERIALS_LIBRARY__HPP
#define RENDERING__MATERIALS_LIBRARY__HPP


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
			MaterialLibrary(const std::string& filePath);
			~MaterialLibrary();

			// Getters
			bool Has(const MaterialType& materialType) const;
			size_t GetSize() const;
			std::string GetMaterialsConfigFilePath() const;
			std::unordered_map<MaterialType, Material> GetMaterials() const;
			Material GetMaterial(const MaterialType& materialType) const;

			bool LoadFromFile(const std::string& filePath);
			bool SaveToFile(const std::string& filePath) const;
			// TODO: Consider adding ability to add, remove and update materials to the config

		private:
			std::string m_materialsConfigFilePath;
			std::unordered_map<MaterialType, Material> m_materials;
		};
	}
}


#endif // RENDERING__MATERIALS_LIBRARY__HPP