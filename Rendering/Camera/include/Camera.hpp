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


#include "pch.hpp"
#include "ICamera.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
        class RENDERING_API Camera
			: public ICamera
        {
        public:
            Camera();
            Camera(const Math::Vec3& position, float yawRadians, float pitchRadians);
			~Camera() override;

            Camera(const Camera& other);
            Camera& operator=(const Camera& other);
            Camera(Camera&& other) noexcept;
            Camera& operator=(Camera&& other) noexcept;

            // Getters
            Math::Mat4 GetViewMatrix() const override;
            Math::Vec3 GetPosition() const override;
            Math::Vec3 GetForward() const override;
            Math::Vec3 GetRight() const override;
            Math::Vec3 GetUp() const override;

            void Rotate(float yaw, float pitch, float roll) override;
            void Zoom(float deltaDistance) override;
            void SetOnDistanceChange(OnDistanceChange callback) override;

        private:
            class CameraImpl;
			CameraImpl* m_pCameraImpl;
        };
	}
}


#endif // RENDERING__CAMERA__HPP