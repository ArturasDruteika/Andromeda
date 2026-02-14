#ifndef RENDERING__OPENGL__SUPPORT__FPS_COUNTER__HPP
#define RENDERING__OPENGL__SUPPORT__FPS_COUNTER__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
    class FpsCounter
    {
    public:
        FpsCounter();
        ~FpsCounter();

        FpsCounter(const FpsCounter& other) = delete;
        FpsCounter& operator=(const FpsCounter& other) = delete;
        FpsCounter(FpsCounter&& other) noexcept = delete;
        FpsCounter& operator=(FpsCounter&& other) noexcept = delete;

        // Call once per frame
        void FrameTick();

        float GetInstantFps() const;
        float GetSmoothedFps() const;

        // Delta time in seconds
        float GetDeltaSeconds() const;

    private:
        std::chrono::steady_clock::time_point m_lastTime;
        float m_deltaSeconds;
        float m_instantFps;
        float m_smoothedFps;
        bool m_firstFrame;
    };
}

#endif // RENDERING__OPENGL__SUPPORT__FPS_COUNTER__HPP
