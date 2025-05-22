#ifndef ENGINECORE__GRAPHICAL_MODAL_WINDOW__HPP
#define ENGINECORE__GRAPHICAL_MODAL_WINDOW__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class GraphicalModalWindow
		{
		public:
			GraphicalModalWindow();
			~GraphicalModalWindow();

			// Getters
			virtual int GetID() = 0;
			virtual float GetWindowWidth() = 0;
			virtual float GetWindowHeight() = 0;
			virtual float GetAvailableWindowWidth() = 0;
			virtual float GetAvailableWindowHeight() = 0;
			virtual std::string GetWindowName() = 0;
			// Setters
			virtual void SetWindowName(const std::string& name) = 0;
			// Functionality
			virtual void Init() = 0;
			virtual void Render() = 0;
			virtual void DeInit() = 0;
		};
	}
}


#endif // ENGINECORE__GRAPHICAL_MODAL_WINDOW__HPP