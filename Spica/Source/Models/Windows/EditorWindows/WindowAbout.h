#pragma once

#include "Models/Windows/EditorWindows/EditorWindow.h"

class WindowAbout : public EditorWindow
{
public:
	WindowAbout();
	~WindowAbout();

	void DrawWindowContents();
};

