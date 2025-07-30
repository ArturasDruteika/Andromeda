#ifndef ENVIRONMENT__ABSTRACTS_SCENE_ENVIRONMENT__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_ENVIRONMENT__HPP


namespace Andromeda::Rendering
{
	class SceneEnvironment
	{
	public:
		SceneEnvironment();
		~SceneEnvironment();

		// Getters
		float GetAmbientStrength() const;
		// Setters
		void SetAmbientStrength(float ambientStrength);

		void ResizeGrid(float resizeFactor);

	protected:
		float m_gridSpacing;
		float m_ambientStrength;
	};
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_ENVIRONMENT__HPP