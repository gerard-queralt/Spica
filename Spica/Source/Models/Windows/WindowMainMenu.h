#pragma once

#include "Models/Windows/Window.h"

#include <list>
#include <vector>

#include "Models/Windows/EditorWindows/EditorWindow.h"
#include "Models/Windows/EditorWindows/WindowAbout.h"

class WindowMainMenu : public Window
{
public:
	WindowMainMenu(const std::vector<EditorWindow*>& i_editorWindows);
	~WindowMainMenu();

	static const std::string s_repositoryLink;

	void Draw(bool& i_enabled = s_default) override;

	inline bool IsWindowEnabled(int i_windowIndex) const {
		return m_windowsEnabled[i_windowIndex];
	}
	inline void SetWindowEnabled(int i_windowIndex, bool i_enabled) {
		m_windowsEnabled[i_windowIndex] = i_enabled;
	}

private:
	void DrawWindowsMenu();
	void DrawAbout();
	void DrawGithubLink() const;
	void DrawExit() const;

	static bool s_default;

	WindowAbout* m_about = nullptr;
	bool m_showAbout = false;

	int m_nWindows;
	std::vector<std::string> m_windowNames;
	std::vector<bool> m_windowsEnabled;
};

