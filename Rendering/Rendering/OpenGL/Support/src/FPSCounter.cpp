#include "../include/FpsCounter.hpp"


namespace Andromeda::Rendering
{
    FpsCounter::FpsCounter()
        : m_lastTime{ std::chrono::steady_clock::now() }
        , m_deltaSeconds{ 0.0f }
        , m_instantFps{ 0.0f }
        , m_smoothedFps{ 0.0f }
        , m_firstFrame{ true }
    {
    }

    FpsCounter::~FpsCounter() = default;

    void FpsCounter::FrameTick()
    {
        auto now = std::chrono::steady_clock::now();

        m_deltaSeconds =
            std::chrono::duration<float>(now - m_lastTime).count();

        m_lastTime = now;

        if (m_deltaSeconds > 0.0f)
        {
            m_instantFps = 1.0f / m_deltaSeconds;
        }
        else
        {
            m_instantFps = 0.0f;
        }

        // Smooth with exponential moving average
        const float alpha = 0.1f; // smoothing factor

        if (m_firstFrame)
        {
            m_smoothedFps = m_instantFps;
            m_firstFrame = false;
        }
        else
        {
            m_smoothedFps =
                alpha * m_instantFps + (1.0f - alpha) * m_smoothedFps;
        }
    }

    float FpsCounter::GetInstantFps() const
    {
        return m_instantFps;
    }

    float FpsCounter::GetSmoothedFps() const
    {
        return m_smoothedFps;
    }

    float FpsCounter::GetDeltaSeconds() const
    {
        return m_deltaSeconds;
    }
}
