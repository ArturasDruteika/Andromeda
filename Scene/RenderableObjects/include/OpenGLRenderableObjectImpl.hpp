#ifndef SCENE__RENDERABLE_OBJECT_IMPL__HPP
#define SCENE__RENDERABLE_OBJECT_IMPL__HPP


#include "../include/OpenGLRenderableObject.hpp"
#include <glm/glm.hpp>



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

			void SetPosition(float x, float y, float z);
			void SetRotation(float pitch, float yaw, float roll);
			void SetScale(float x, float y, float z);

			std::vector<float> GetPosition();
			std::vector<float> GetRotation();
			std::vector<float> GetScale();

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