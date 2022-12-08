#include "WindowAbout.h"

#include "imgui.h"

WindowAbout::WindowAbout() : EditorWindow("About")
{
}

WindowAbout::~WindowAbout()
{
}

void WindowAbout::DrawWindowContents()
{
	ImGui::TextUnformatted((std::string(TITLE) + " Engine").c_str());
	ImGui::TextWrapped("A prototype game engine made in C++ from scratch");
	ImGui::Separator();
	ImGui::TextUnformatted("Author: Gerard Queralt");
	ImGui::TextUnformatted("License: MIT");
}
