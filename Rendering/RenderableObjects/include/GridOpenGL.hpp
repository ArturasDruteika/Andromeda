#ifndef RENDERING__GRID_OPENGL__HPP
#define RENDERING__GRID_OPENGL__HPP


#include "IRenderableObjectOpenGL.hpp"
#include "RenderableObjectOpenGLBase.hpp"
#include "Colors.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class GridOpenGL
			: public IRenderableObjectOpenGL
			, private RenderableObjectOpenGLBase
		{	
		public:
			GridOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color);
			~GridOpenGL();

			GridOpenGL(const GridOpenGL& other) = delete;	// Prevent Copy Constructor
			GridOpenGL& operator=(const GridOpenGL& other) = delete;	// Prevent Copy Assignment
			GridOpenGL(GridOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
			GridOpenGL& operator=(GridOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

		private:
			void ConstructGrid(int size = 100, const Space::Color& gridColor = { 0.3, 0.3, 0.3, 1.0 });

		};
	}
}


#endif // RENDERING__GRID_OPENGL__HPP