#ifndef RENDERING__INTERFACES__I_RENDERABLE_OBJECT_OPEN_GL__HPP
#define RENDERING__INTERFACES__I_RENDERABLE_OBJECT_OPEN_GL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "Andromeda/RenderableObjects/IRenderableObject.hpp"
#include "../../../Vertices/include/VertexLayouts.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IRenderableObjectOpenGL
		: public IRenderableObject
	{	
	public:
		virtual ~IRenderableObjectOpenGL();

		// Getters
		virtual unsigned int GetVBO() const = 0;
		virtual unsigned int GetVAO() const = 0;
		virtual unsigned int GetEBO() const = 0;
	};
}


#endif // RENDERING__INTERFACES__I_RENDERABLE_OBJECT_OPEN_GL__HPP