#ifndef ENGINECORE__GRAPHICAL_MODAL_WINDOW__HPP
#define ENGINECORE__GRAPHICAL_MODAL_WINDOW__HPP


namespace Andromeda
{
	namespace EngineCore
	{
		class GraphicalModalWindow
		{
		public:
			GraphicalModalWindow();
			~GraphicalModalWindow();

			GraphicalModalWindow(const GraphicalModalWindow& other) = delete;	// Prevent Copy Constructor
			GraphicalModalWindow& operator=(const GraphicalModalWindow& other) = delete;	// Prevent Copy assignment
			GraphicalModalWindow(GraphicalModalWindow&& other) noexcept = delete;	// Prevent Move constructor
			GraphicalModalWindow& operator=(const GraphicalModalWindow&& other) noexcept = delete;	//Prevent Move assignment

			void Init();
			void Render();
			void DeInit();

		private:
			class GraphicalModalWindowImpl;
			GraphicalModalWindowImpl* m_pGraphicalModalWindowImpl;
		};
	}
}


#endif // ENGINECORE__GRAPHICAL_MODAL_WINDOW__HPP