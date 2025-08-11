#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP


#include "../../MacroExports/include/MacroExports.hpp"
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