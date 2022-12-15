#include "MicrosecondTimer.h"

Uint64 MicrosecondTimer::s_performanceFrequency = SDL_GetPerformanceFrequency();

MicrosecondTimer::MicrosecondTimer()
{
}

MicrosecondTimer::~MicrosecondTimer()
{
}

unsigned long long MicrosecondTimer::GetCurrentTime() const
{
	return SDL_GetPerformanceCounter();
}

void MicrosecondTimer::UpdateDeltaTime()
{
	m_deltaTime = (GetCurrentTime() - m_startTime) * 1000000L / s_performanceFrequency;
}
