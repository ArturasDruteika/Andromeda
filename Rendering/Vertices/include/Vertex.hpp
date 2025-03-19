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
#include "../../Attributes/include/Colors.hpp"
#include "../../Attributes/include/Points.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API Vertex
		{
		public:
			Vertex(const Point3D& point3D, const Color& color);
			~Vertex();

			Vertex(const Vertex& other);
			Vertex& operator=(const Vertex& other) = delete;	// Prevent Copy Assignment
			Vertex(Vertex&& other) noexcept = delete;	// Prevent Move Constructor
			Vertex& operator=(Vertex&& other) noexcept = delete;	// Prevent Move Assignment

			Point3D GetPosition() const;
			void SetPosition(const Point3D& color);
			Color GetColor() const;
			void SetColor(const Color& color);

		private:
			class VertexImpl;
			VertexImpl* m_pVertexImpl;
		};
	}
}


#endif // RENDERING__VERTEX__HPP