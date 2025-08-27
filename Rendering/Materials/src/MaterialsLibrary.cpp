#include "../include/MaterialsLibrary.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "json.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda
{
	namespace Rendering
	{
		// Helper to map string --> MaterialType
		// Throws if name not recognized.
		static MaterialType materialTypeFromString(const std::string& s) {
			if (s == "emerald")       return MaterialType::Emerald;
			if (s == "jade")          return MaterialType::Jade;
			if (s == "obsidian")      return MaterialType::Obsidian;
			if (s == "pearl")         return MaterialType::Pearl;
			if (s == "ruby")          return MaterialType::Ruby;
			if (s == "turquoise")     return MaterialType::Turquoise;
			if (s == "brass")         return MaterialType::Brass;
			if (s == "bronze")        return MaterialType::Bronze;
			if (s == "chrome")        return MaterialType::Chrome;
			if (s == "copper")        return MaterialType::Copper;
			if (s == "gold")          return MaterialType::Gold;
			if (s == "silver")        return MaterialType::Silver;
			if (s == "black plastic") return MaterialType::BlackPlastic;
			if (s == "cyan plastic")  return MaterialType::CyanPlastic;
			if (s == "green plastic") return MaterialType::GreenPlastic;
			if (s == "red plastic")   return MaterialType::RedPlastic;
			if (s == "white plastic") return MaterialType::WhitePlastic;
			if (s == "yellow plastic")return MaterialType::YellowPlastic;
			if (s == "black rubber")  return MaterialType::BlackRubber;
			if (s == "cyan rubber")   return MaterialType::CyanRubber;
			if (s == "green rubber")  return MaterialType::GreenRubber;
			if (s == "red rubber")    return MaterialType::RedRubber;
			if (s == "white rubber")  return MaterialType::WhiteRubber;
			if (s == "yellow rubber") return MaterialType::YellowRubber;
			throw std::runtime_error("Unknown material name: " + s);
		}


		MaterialLibrary::MaterialLibrary()
		{
		}

		MaterialLibrary::MaterialLibrary(const std::filesystem::path& filePath)
			: m_materialsConfigFilePath{ filePath }
		{
			LoadFromFile(filePath);
		}

		MaterialLibrary::~MaterialLibrary() = default;

		bool MaterialLibrary::Has(const MaterialType& materialType) const
		{
			return m_materials.find(materialType) != m_materials.end();
		}

		size_t MaterialLibrary::GetSize() const
		{
			return m_materials.size();
		}

		std::filesystem::path MaterialLibrary::GetMaterialsConfigFilePath() const
		{
			return m_materialsConfigFilePath;
		}

		std::unordered_map<MaterialType, Material> MaterialLibrary::GetMaterials() const
		{
			return m_materials;
		}

		Material MaterialLibrary::GetMaterial(const MaterialType& materialType) const
		{
			std::unordered_map<MaterialType, Material>::const_iterator it = m_materials.find(materialType);

			if (it == m_materials.end()) 
			{
				spdlog::error(
					"MaterialLibrary::GetMaterial - material '{}' not found; returning default",
					static_cast<int>(materialType)
				);
				return Material{};
			}
			return it->second;
		}


		bool MaterialLibrary::LoadFromFile(const std::filesystem::path& filePath)
		{
			std::ifstream in(filePath);
			if (!in.is_open()) 
			{
				spdlog::error("File {} is open.", filePath.string());
				return false;
			}

			nlohmann::json j;
			in >> j;
			if (!j.is_array()) 
			{
				spdlog::error("It is not a JSON array.");
				return false;
			}

			m_materials.clear();

			for (auto& entry : j)
			{
				// Required fields
				std::string name = entry.at("name").get<std::string>();
				auto& amb = entry.at("ambient");
				auto& dif = entry.at("diffuse");
				auto& spec = entry.at("specular");
				float shininess = entry.at("shininess").get<float>();

				// Build Material struct
				Material mat;
				mat.SetShininess(shininess);
				mat.SetName(name);
				mat.SetAmbient({ amb[0].get<float>(), amb[1].get<float>(), amb[2].get<float>() });
				mat.SetDiffuse({ dif[0].get<float>(), dif[1].get<float>(), dif[2].get<float>() });
				mat.SetSpecular({ spec[0].get<float>(), spec[1].get<float>(), spec[2].get<float>() });

				// Map to enum and insert
				MaterialType type = materialTypeFromString(name);
				m_materials[type] = std::move(mat);
			}
			m_materialsConfigFilePath = filePath;

			return true;
		}

		bool MaterialLibrary::SaveToFile(const std::filesystem::path& filePath) const
		{
			spdlog::info("Saving {} materials to \"{}\"", m_materials.size(), filePath.string());

			// Build a JSON array
			nlohmann::json j = nlohmann::json::array();
			for (const auto& kv : m_materials)
			{
				const Material& m = kv.second;
				nlohmann::json entry;
				Math::Vec3 ambient = m.GetAmbient();
				Math::Vec3 diffuse = m.GetDiffuse();
				Math::Vec3 specular = m.GetSpecular();
				entry["name"] = m.GetName();
				entry["ambient"] = { ambient[0], ambient[1], ambient[2] };
				entry["diffuse"] = { diffuse[0],  diffuse[1],  diffuse[2] };
				entry["specular"] = { specular[0], specular[1], specular[2] };
				entry["shininess"] = m.GetShininess();
				j.push_back(std::move(entry));
			}

			// Open output file
			std::ofstream out(filePath);
			if (!out.is_open()) 
			{
				spdlog::error("MaterialLibrary::SaveToFile - failed to open \"{}\" for writing", filePath.string());
				return false;
			}

			out << std::fixed
				<< std::setprecision(4)
				<< std::setw(4)
				<< j << std::endl;
			if (!out.good()) 
			{
				spdlog::error("MaterialLibrary::SaveToFile - error occurred while writing to \"{}\"", filePath.string());
				return false;
			}

			spdlog::info("Successfully wrote material data to \"{}\"", filePath.string());
			return true;
		}
	}
}
