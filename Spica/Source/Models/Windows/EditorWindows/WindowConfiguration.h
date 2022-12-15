#pragma once

#include "EditorWindow.h"
#include "Models/Windows/SubWindows/SubWindow.h"

#include <vector>

class WindowConfiguration : public EditorWindow
{
public:
	WindowConfiguration();
	~WindowConfiguration();

protected:
	void DrawWindowContents() override;

private:
	std::vector<SubWindow*> m_collapsingSubWindows;
};

