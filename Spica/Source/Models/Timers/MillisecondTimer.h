#pragma once

#include "Timer.h"

class MillisecondTimer : public Timer
{
public:
	MillisecondTimer();
	~MillisecondTimer();

protected:
	unsigned long long GetCurrentTime();
	void UpdateDeltaTime();
};

