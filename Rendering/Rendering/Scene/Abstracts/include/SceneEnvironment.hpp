#ifndef ENVIRONMENT__ABSTRACTS_SCENE_ENVIRONMENT__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_ENVIRONMENT__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
	class SceneEnvironment
	{
	public:
		SceneEnvironment();
		~SceneEnvironment();

		// Getters
		float GetAmbientStrength() const;
		const Math::Vec4& GetBackgroundColor() const;
		// Setters
		void SetAmbientStrength(float ambientStrength);
		void SetBackgroundColor(const Math::Vec4& backroundColor);

		void ResizeGrid(float resizeFactor);

	protected:
		float m_gridSpacing;
		float m_ambientStrength;
		Math::Vec4 m_backroundColor;
	};
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_ENVIRONMENT__HPP