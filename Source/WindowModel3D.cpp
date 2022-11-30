#include "WindowModel3D.h"

#include "imgui.h"

WindowModel3D::WindowModel3D() : Window("Model Information")
{
}

WindowModel3D::~WindowModel3D()
{
}

update_status WindowModel3D::Update()
{
	if (m_model != nullptr) {
		bool enabled;

		if (ImGui::Begin(m_name.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
			std::list<Mesh*> modelMeshes = m_model->m_meshes;
			int meshNumber = 1;
			for (std::list<Mesh*>::iterator it = modelMeshes.begin(); it != modelMeshes.end(); ++it) {
				std::string menuName = "Mesh " + std::to_string(meshNumber);
				if (ImGui::BeginMenu(menuName.c_str())) {
					int meshNumVertices = (*it)->m_numVertices;
					ImGui::TextUnformatted(("Num Vertices: " + std::to_string(meshNumVertices)).c_str());
					int meshNumTriangles = (*it)->m_numTriangles;
					ImGui::TextUnformatted(("Num Triangles: " + std::to_string(meshNumTriangles)).c_str());
					int meshTextureIndex = (*it)->m_materialIndex;
					ImGui::TextUnformatted(("Texture Index: " + std::to_string(meshTextureIndex)).c_str());
					ImGui::EndMenu();
				}
				++meshNumber;
			}
		}
		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

void WindowModel3D::SetModel(const Model3D* i_model)
{
	m_model = i_model;
}