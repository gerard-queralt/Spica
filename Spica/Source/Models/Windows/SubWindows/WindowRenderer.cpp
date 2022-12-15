#include "WindowRenderer.h"

#include "imgui.h"

#include "Application.h"
#include "Modules/ModuleRender.h"

int WindowRenderer::s_bufferSize = 128;

WindowRenderer::WindowRenderer() : SubWindow("Renderer")
{
	m_vertexShaderBuffer = App->renderer->GetVertexShader();
	m_fragmentShaderBuffer = App->renderer->GetFragmentShader();
}

WindowRenderer::~WindowRenderer()
{
}

void WindowRenderer::DrawWindowContents()
{
	ImGui::TextUnformatted("Vertex shader");
	ImGui::InputText("##vertex shader", &m_vertexShaderBuffer[0], s_bufferSize);
	ImGui::TextUnformatted("Fragment shader");
	ImGui::InputText("##fragment shader", &m_fragmentShaderBuffer[0], s_bufferSize);

	ImGui::Dummy(ImVec2(0.f, 5.f)); //spacing
	if (ImGui::Button("Update shaders")) {
		App->renderer->SetShaders(m_vertexShaderBuffer, m_fragmentShaderBuffer);
	}
}
