#pragma once

#include "Timer.h"

#include "SDL.h"

class MicrosecondTimer : public Timer
{
public:
	MicrosecondTimer();
	~MicrosecondTimer();

protected:
	unsigned long long GetCurrentTime();
	void UpdateDeltaTime();

private:
	static Uint64 s_performanceFrequency;
};

