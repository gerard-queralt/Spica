#include "WindowModel3D.h"

#include "imgui.h"

WindowModel3D::WindowModel3D() : EditorWindow("Model Information")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}

WindowModel3D::~WindowModel3D()
{
}

void WindowModel3D::DrawWindowContents()
{
	if (m_model != nullptr) {
		//AABB related info
		AABB* modelAABB = m_model->m_aabb;
		std::string centerFormatted = FormatFloat3AsString(modelAABB->CenterPoint());
		ImGui::TextUnformatted(("AABB Center: " + centerFormatted).c_str());
		std::string minPoint = FormatFloat3AsString(modelAABB->minPoint);
		ImGui::TextUnformatted(("AABB Min Point: " + minPoint).c_str());
		std::string maxPoint = FormatFloat3AsString(modelAABB->maxPoint);
		ImGui::TextUnformatted(("AABB Max Point: " + maxPoint).c_str());

		ImGui::Separator();

		//Mesh related information
		std::vector<Mesh*> modelMeshes = m_model->m_meshes;
		for (int i = 0; i < modelMeshes.size(); ++i) {
			std::string menuName = "Mesh " + std::to_string(i);
			Mesh* currentMesh = modelMeshes[i];
			if (ImGui::CollapsingHeader(menuName.c_str())) {
				int meshNumVertices = currentMesh->m_numVertices;
				ImGui::TextUnformatted(("Num Vertices: " + std::to_string(meshNumVertices)).c_str());
				int meshNumTriangles = currentMesh->m_numTriangles;
				ImGui::TextUnformatted(("Num Triangles: " + std::to_string(meshNumTriangles)).c_str());
				int meshTextureWidth = currentMesh->m_textureWidth;
				ImGui::TextUnformatted(("Texture Width: " + std::to_string(meshTextureWidth)).c_str());
				int meshTextureHeight = currentMesh->m_textureHeight;
				ImGui::TextUnformatted(("Texture Height: " + std::to_string(meshTextureHeight)).c_str());
			}
		}
	}
}

std::string WindowModel3D::FormatFloat3AsString(const float3& i_point) const
{
	return std::to_string(i_point.x) + ", " + std::to_string(i_point.y) + ", " + std::to_string(i_point.z);
}
