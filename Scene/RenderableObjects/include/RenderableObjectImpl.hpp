#ifndef SCENE__RENDERABLE_OBJECT_IMPL__HPP
#define SCENE__RENDERABLE_OBJECT_IMPL__HPP


#include "../include/RenderableObject.hpp"


namespace Andromeda
{
	namespace Scene
	{
		class OpenGLRenderableObject::OpenGLRenderableObjectImpl
		{
		public:
			OpenGLRenderableObjectImpl(const std::vector<float>& vertices);
			~OpenGLRenderableObjectImpl();

			OpenGLRenderableObjectImpl(const OpenGLRenderableObjectImpl& other) = delete;	// Prevent Copy Constructor
			OpenGLRenderableObjectImpl& operator=(const OpenGLRenderableObjectImpl& other) = delete;	// Prevent Copy Assignment
			OpenGLRenderableObjectImpl(OpenGLRenderableObjectImpl&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLRenderableObjectImpl& operator=(OpenGLRenderableObjectImpl&& other) noexcept = delete;	// Prevent Move Assignment

		private:
			void Init(const std::vector<float>& vertices);

			unsigned int m_VBO;
			unsigned int m_VAO;
			glm::vec3 m_position;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
			unsigned int m_vertextCount;
		};
	}
}


#endif // SCENE__RENDERABLE_OBJECT_IMPL__HPP