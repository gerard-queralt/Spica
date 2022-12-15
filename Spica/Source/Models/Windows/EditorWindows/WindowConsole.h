#pragma once

#include "EditorWindow.h"

class WindowConsole : public EditorWindow
{
public:
	WindowConsole();
	~WindowConsole();

	void Output(const char* i_textToPrint);

protected:
	void DrawWindowContents() override;

private:
	ImVector<const char*> m_consloneContents;
};

