#pragma once

#include "SubWindow.h"

#include <vector>

class WindowFPS : public SubWindow
{
public:
	WindowFPS();
	~WindowFPS();

protected:
	void DrawWindowContents() override;

private:
	int m_fpsCaptures = 100;
	int m_currentIndex = 0;
	std::vector<float> m_fpsHist;
};

