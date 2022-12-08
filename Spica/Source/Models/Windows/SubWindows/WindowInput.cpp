#include "WindowInput.h"

#include "imgui.h"

#include "Application.h"
#include "Modules/ModuleInput.h"

WindowInput::WindowInput() : SubWindow("Input")
{
}

WindowInput::~WindowInput()
{
}

void WindowInput::DrawWindowContents()
{
	ImGui::TextUnformatted("Camera speed");
	ImGui::SliderFloat("##movement", &App->input->m_cameraSpeed, 0.01f, 0.1f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::TextUnformatted("Rotation speed");
	ImGui::SliderFloat("##rotation", &App->input->m_angleSpeed, 0.0001f, 0.01f, "%.4f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::TextUnformatted("Zoom speed");
	ImGui::SliderFloat("##zoom", &App->input->m_zoomSpeed, 0.001f, 0.01f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
}
