#include "WindowConfiguration.h"

#include "Models/Windows/SubWindows/WindowFPS.h"
#include "Models/Windows/SubWindows/WindowWindow.h"
#include "Models/Windows/SubWindows/WindowInput.h"
#include "Models/Windows/SubWindows/WindowRenderer.h"
#include "Models/Windows/SubWindows/WindowCamera.h"

WindowConfiguration::WindowConfiguration() : EditorWindow("Configuration")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	m_collapsingSubWindows.push_back(new WindowFPS());
	m_collapsingSubWindows.push_back(new WindowWindow());
	m_collapsingSubWindows.push_back(new WindowInput());
	m_collapsingSubWindows.push_back(new WindowRenderer());
	m_collapsingSubWindows.push_back(new WindowCamera());
}

WindowConfiguration::~WindowConfiguration()
{
	for (SubWindow* window : m_collapsingSubWindows)
		delete window;
	m_collapsingSubWindows.clear();
}

void WindowConfiguration::DrawWindowContents()
{
	for (SubWindow* subWindow : m_collapsingSubWindows)
		subWindow->Draw();
}
