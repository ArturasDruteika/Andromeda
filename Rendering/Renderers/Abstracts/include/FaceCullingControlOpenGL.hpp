#ifndef RENDERER__FACE_CULLING_CONTROL_OPENGL__HPP
#define RENDERER__FACE_CULLING_CONTROL_OPENGL__HPP


namespace Andromeda::Rendering
{
	class FaceCullingControlOpenGL
	{
	public:
		FaceCullingControlOpenGL();
		~FaceCullingControlOpenGL();

		// Getters
		bool IsFaceCullingEnabled() const;
		bool IsBackFaceCullingEnabled() const;

		void EnableFaceCulling(unsigned int face, unsigned int winding) const;
		void DisableFaceCulling() const;

	protected:
		mutable bool m_isFaceCullingEnabled;
		mutable bool m_isBackFaceCullingEnabled;
	};
}


#endif // RENDERER__FACE_CULLING_CONTROL_OPENGL__HPP