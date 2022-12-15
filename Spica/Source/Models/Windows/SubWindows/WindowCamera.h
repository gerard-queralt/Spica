#pragma once

#include "Models/Windows/SubWindows/SubWindow.h"

class WindowCamera : public SubWindow
{
public:
	WindowCamera();
	~WindowCamera();

protected:
	void DrawWindowContents() override;
};

