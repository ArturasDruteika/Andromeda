#ifndef RENDERING__VERTEX__HPP
#define RENDERING__VERTEX__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif

#include "pch.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API Vertex
		{
		public:
			Vertex(float x, float y, float z, float r, float g, float b);
			~Vertex();

			Vertex(const Vertex& other) = delete;	// Prevent Copy Constructor
			Vertex& operator=(const Vertex& other) = delete;	// Prevent Copy Assignment
			Vertex(Vertex&& other) noexcept = delete;	// Prevent Move Constructor
			Vertex& operator=(Vertex&& other) noexcept = delete;	// Prevent Move Assignment

			std::array<float, 3> GetPosition() const;
			void SetPosition(float x, float y, float z);
			std::array<float, 3> GetColor() const;
			void SetColor(float r, float g, float b);

		private:
			class VertexImpl;
			VertexImpl* m_pVertexImpl;
		};
	}
}


#endif // RENDERING__VERTEX__HPP