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

            Camera(const Camera& other);	// Prevent Copy Constructor
            Camera& operator=(const Camera& other);	// Prevent Copy Assignment
            Camera(Camera&& other);	// Prevent Move Constructor
            Camera& operator=(Camera&& other);	// Prevent Move Assignment

            // Getters
            float GetYaw() const;
			float GetPitch() const;
            Math::Mat4 GetViewMatrix() const;
            Math::Vec3 GetPosition() const;
            Math::Vec3 GetForward() const;
            Math::Vec3 GetRight() const;
            Math::Vec3 GetUp() const;
            // Setters
            void SetPosition(const Math::Vec3& position);
            void SetRotation(float yawRadians, float pitchRadians);

            void Move(const Math::Vec3& delta);
            void Rotate(float deltaYawRad, float deltaPitchRad);

            bool IsUpsideDown() const;

        private:
            class CameraImpl;
			CameraImpl* m_pCameraImpl;
        };
	}
}


#endif // RENDERING__CAMERA__HPP