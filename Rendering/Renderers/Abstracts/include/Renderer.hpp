#ifndef RENDERER__RENDERER__HPP
#define RENDERER__RENDERER__HPP


#include "../include/CameraControl.hpp"
#include "../include/GridControl.hpp"
#include "../include/IlluminationControl.hpp"
#include "../include/SizeControl.hpp"
#include "Andromeda/Scene/IScene.hpp"


namespace Andromeda::Rendering
{
	class Renderer
		: public CameraControl
		, public GridControl
		, public IlluminationControl
		, public SizeControl
	{
	public:
		Renderer();
		~Renderer();

		// Getters
		bool IsInitialized() const;

		void Init(int width, int height, bool illuminationMode = false);
		void DeInit();
		void RenderFrame(IScene& scene);

	protected:
		bool m_initialized;
	};
}


#endif // RENDERER__RENDERER__HPP