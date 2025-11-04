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
		SkyroomOpenGLImpl(const Math::Vec3& centerPosition, float halfExtent, const Space::Color& color);
		~SkyroomOpenGLImpl();

		float GetHalfExtent() const;

	private:
		void BuildGeometry(float h, const Space::Color& colorGray);

	private:
		float m_halfExtent;
	};
}


#endif // RENDERING__OBJECTS__SKYROOM_IMPL_OPENGL__HPP