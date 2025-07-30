#ifndef ENVIRONMENT__ABSTRACTS_SCENE_STATE__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_STATE__HPP


namespace Andromeda::Rendering
{
	class SceneState
	{
	public:
		SceneState();
		~SceneState();

		bool StateChanged() const;
		void ResetState();

	protected:
		bool m_stateChanged;
	};
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_STATE__HPP