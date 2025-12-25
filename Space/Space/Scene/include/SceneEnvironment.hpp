#ifndef SPACE__SCENE__SCENE_API__SCENE__HPP
#define SPACE__SCENE__SCENE_API__SCENE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneEnvironment.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API SceneEnvironment
		: public virtual ISceneEnvironment
	{
	public:
		SceneEnvironment();
		~SceneEnvironment() override;

		// Getters
		float GetAmbientStrength() const override;
		const Math::Vec4& GetBackgroundColor() const override;
		// Setters
		void SetAmbientStrength(float ambientStrength) override;
		void SetBackgroundColor(const Math::Vec4& backroundColor) override;

		void ResizeGrid(float resizeFactor) override;

	protected:
		float m_ambientStrength;
		Math::Vec4 m_backgroundColor;
	};
}


#endif // SPACE__SCENE__SCENE_API__SCENE__HPP