#include "WindowWindow.h"

#include "imgui.h"

#include "Application.h"
#include "Modules/ModuleWindow.h"

WindowWindow::WindowWindow() : SubWindow("Window")
{
}

WindowWindow::~WindowWindow()
{
}

void WindowWindow::DrawWindowContents()
{
	float brightness = App->window->GetWindowBrightness();
	ImGui::TextUnformatted("Window Brightness");
	bool brightnessChanged = ImGui::SliderFloat("##bright", &brightness, .25f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
	if (brightnessChanged)
		App->window->SetWindowBrightness(brightness);

	int width, height;
	SDL_GetWindowSize(App->window->m_window, &width, &height);
	ImGui::TextUnformatted("Window Width");
	bool widthChanged = ImGui::SliderInt("##width", &width, 640, 1920, "%d", ImGuiSliderFlags_AlwaysClamp);
	ImGui::TextUnformatted("Window Height");
	bool heighChanged = ImGui::SliderInt("##height", &height, 360, 1080, "%d", ImGuiSliderFlags_AlwaysClamp);
	if (widthChanged || heighChanged)
		App->window->ResizeWindow(width, height);

	bool fullscreen = App->window->IsWindowFullscreen();
	if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
		App->window->SetFullscreen(fullscreen);
	}

	ImGui::SameLine();

	bool resizable = App->window->IsWindowResizable();
	if (ImGui::Checkbox("Resizable", &resizable)) {
		App->window->SetResizable(resizable);
	}
		
	bool borderless = App->window->IsWindowBorderless();
	if (ImGui::Checkbox("Borderless", &borderless)) {
		App->window->SetBorderless(borderless);
	}

	ImGui::SameLine();

	bool fullDesktop = App->window->IsWindowDesktopFullscreen();
	if (ImGui::Checkbox("Desktop Fullscreen", &fullDesktop)) {
		App->window->SetDesktopFullscreen(fullDesktop);
	}
}
