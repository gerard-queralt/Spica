#pragma once

#include "SubWindow.h"

class WindowInput : public SubWindow
{
public:
	WindowInput();
	~WindowInput();

protected:
	void DrawWindowContents() override;
};

