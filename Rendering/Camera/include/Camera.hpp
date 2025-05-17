#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP


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


#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
        class RENDERING_API Camera
        {
        public:
            Camera();
            Camera(const Math::Vec3& position, float yawRadians, float pitchRadians);
			~Camera();

            Camera(const Camera& other);
            Camera& operator=(const Camera& other);
            Camera(Camera&& other) noexcept;
            Camera& operator=(Camera&& other) noexcept;

            // Getters
            Math::Mat4 GetViewMatrix() const;
            Math::Vec3 GetPosition() const;
            Math::Vec3 GetForward() const;
            Math::Vec3 GetRight() const;
            Math::Vec3 GetUp() const;

            void Rotate(float yaw, float pitch, float roll);

        private:
            class CameraImpl;
			CameraImpl* m_pCameraImpl;
        };
	}
}


#endif // RENDERING__CAMERA__HPP