#include "MillisecondTimer.h"

#include "SDL.h"

MillisecondTimer::MillisecondTimer()
{
}

MillisecondTimer::~MillisecondTimer()
{
}

unsigned long long MillisecondTimer::GetCurrentTime()
{
	return SDL_GetTicks();
}

void MillisecondTimer::UpdateDeltaTime()
{
	m_deltaTime = GetCurrentTime() - m_startTime;
}
