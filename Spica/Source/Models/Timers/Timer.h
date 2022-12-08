#pragma once

class Timer
{
public:
	void Start();
	unsigned long long Read();
	unsigned long long Stop();

protected:
	virtual unsigned long long GetCurrentTime() = 0;
	virtual void UpdateDeltaTime() = 0;

	unsigned long long m_startTime = 0L;
	unsigned long long m_deltaTime = 0L;
	bool m_stopped = false;
};

