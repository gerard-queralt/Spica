#include "Timer.h"

void Timer::Start()
{
    m_stopped = false;
    m_startTime = GetCurrentTime();
    m_deltaTime = 0;
}

unsigned long long Timer::Read()
{
    if (!m_stopped) {
        UpdateDeltaTime();
    }
    return m_deltaTime;
}

unsigned long long Timer::Stop()
{
    UpdateDeltaTime();
    m_stopped = true;
    return Read();
}
