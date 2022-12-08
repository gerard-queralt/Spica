#include "WindowCamera.h"

#include "imgui.h"

#include "Application.h"
#include "Modules/ModuleEditorCamera.h"

WindowCamera::WindowCamera() : SubWindow("Camera")
{
}

WindowCamera::~WindowCamera()
{
}

void WindowCamera::DrawWindowContents()
{
	float fov = App->camera->GetFOVdeg();
	ImGui::TextUnformatted("FOV");
	if (ImGui::SliderFloat("##fov", &fov, 60.f, 120.f, "%.0f", ImGuiSliderFlags_AlwaysClamp)) {
		App->camera->SetFOVdeg(fov);
	}
	float nearDistance = App->camera->GetNearPlaneDistance();
	float farDistance = App->camera->GetFarPlaneDistance();
	ImGui::TextUnformatted("Near plane distance");
	bool nearDistanceChanged = ImGui::SliderFloat("##near", &nearDistance, 0.1f, 200.f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::TextUnformatted("Far plane distance");
	bool farDistanceChanged = ImGui::SliderFloat("##far", &farDistance, 0.1f, 200.f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
	if (nearDistanceChanged || farDistanceChanged) {
		App->camera->SetPlaneDistances(nearDistance, farDistance);
	}
}
