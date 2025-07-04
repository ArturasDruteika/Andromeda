#ifndef RENDERING__MATERIALS_LIBRARY__HPP
#define RENDERING__MATERIALS_LIBRARY__HPP


#include "pch.hpp"
#include "Materials.hpp"
#include "json.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class MaterialLibrary
		{
		public:
			MaterialLibrary();
			~MaterialLibrary();

			bool LoadFromFile(const std::string& filePath);

		private:
			std::unordered_map<MaterialType, Material> m_materials;
		};
	}
}


#endif // RENDERING__MATERIALS_LIBRARY__HPP