#ifndef RENDERING__OBJECTS__SKYROOM_IMPL_OPENGL__HPP
#define RENDERING__OBJECTS__SKYROOM_IMPL_OPENGL__HPP


#include "SkyroomOpenGL.hpp"
#include "../../Abstracts/include/RenderableObjectOpenGL.hpp"


namespace Andromeda::Rendering
{
	class SkyroomOpenGL::SkyroomOpenGLImpl
		: public RenderableObjectOpenGL
	{
	public:
		SkyroomOpenGLImpl(const Math::Vec3& centerPosition, const Space::Color& color);
		~SkyroomOpenGLImpl();
	};
}


#endif // RENDERING__OBJECTS__SKYROOM_IMPL_OPENGL__HPP