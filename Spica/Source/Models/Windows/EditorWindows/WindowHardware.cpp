#include "WindowHardware.h"

#include <cmath>

#include "imgui.h"
#include "glew.h"
#include "SDL.h"
#include "assimp/version.h"
#include "d3d9.h"

WindowHardware::WindowHardware() : EditorWindow("Hardware")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	GetCPUinfo();
	GetCaps();
	GetGPUinfo();
}

WindowHardware::~WindowHardware()
{
}

void WindowHardware::DrawWindowContents()
{
	GetSoftwareVersions();

	ImGui::TextUnformatted(("glew Version: " + m_glewVersion).c_str());
	ImGui::TextUnformatted(("OpenGL Version: " + m_openGLVersion).c_str());
	ImGui::TextUnformatted(("SDL Version: " + m_sdlVersion).c_str());
	ImGui::TextUnformatted(("assimp Version: " + m_assimpVersion).c_str());
	ImGui::TextUnformatted(("DirectXTex Version: " + m_dirextXTexVersion).c_str());
	ImGui::TextUnformatted(("ImGui Version: " + m_imguiVersion).c_str());
	ImGui::TextUnformatted(("MathGeoLib Version: " + m_mathGeoLibVersion).c_str());

	ImGui::Separator();

	ImGui::TextUnformatted(("CPUs: " + m_cpusAndCache).c_str());
	ImGui::TextUnformatted(("System RAM: " + m_ram).c_str());
	ImGui::TextUnformatted("Caps: ");
	ImGui::SameLine();
	ImGui::TextWrapped(m_caps.c_str());

	ImGui::Separator();

	ImGui::TextUnformatted(("GPU: " + m_gpuVendorAndDevice).c_str());
	ImGui::TextUnformatted(("Brand: " + m_gpuBrand).c_str());
}

void WindowHardware::GetSoftwareVersions()
{
	//this needs to be done after all modules have been initialized
	//this way is a bit ugly but otherwise it would require a Start/Init function in Window that would be useless for the others
	if (!m_versionsSet) {
		m_versionsSet = true;

		char glewVersion[128];
		sprintf(glewVersion, "%s", glewGetString(GLEW_VERSION));
		m_glewVersion = std::string(glewVersion);

		char glSupported[128];
		sprintf(glSupported, "%s", glGetString(GL_VERSION));
		m_openGLVersion = std::string(glSupported);

		m_sdlVersion = FormatVersion(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

		m_assimpVersion = FormatVersion(aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());

		m_dirextXTexVersion = "1.9.7";

		m_mathGeoLibVersion = "2.0";

		m_imguiVersion = IMGUI_VERSION;
	}
}

void WindowHardware::GetCPUinfo()
{
	int cacheSizeInB = SDL_GetCPUCacheLineSize();
	int cacheSizeInKB = std::ceil(cacheSizeInB / 1000.f);
	int cacheSizeInKb = cacheSizeInKB * 8;
	m_cpusAndCache = std::to_string(SDL_GetCPUCount()) + " (Cache: " + std::to_string(cacheSizeInKb) + "kb)";
}

void WindowHardware::GetCaps()
{
	m_caps = "";
	if (SDL_Has3DNow())
		m_caps += "3DNow ";
	if (SDL_HasAltiVec())
		m_caps += "AltiVec ";
	if (SDL_HasAVX())
		m_caps += "AVX ";
	if (SDL_HasAVX2())
		m_caps += "AVX2 ";
	if (SDL_HasMMX())
		m_caps += "MMX ";
	if (SDL_HasRDTSC())
		m_caps += "RDTSC ";
	if (SDL_HasSSE())
		m_caps += "SSE ";
	if (SDL_HasSSE2())
		m_caps += "SSE2 ";
	if (SDL_HasSSE3())
		m_caps += "SSE3 ";
	if (SDL_HasSSE41())
		m_caps += "SSE41 ";
	if (SDL_HasSSE42())
		m_caps += "SSE42 ";
}

void WindowHardware::GetGPUinfo()
{
	int ramInMB = SDL_GetSystemRAM();
	float ramInGB = ramInMB / 1000.f;
	float ramInGb = ramInGB * 8.f;
	//this is the value multiplied by 10 to the power of 8
	//insted of to the power of 9, which is what Giga is
	//this is to make rounding easier,
	//since I can't find a way to set decimal precision
	int ramInGbOneDecimalAux = std::ceil(ramInGb * 10.f);
	std::string ramInGbOneDecimal = std::to_string(ramInGbOneDecimalAux);
	//insert a dot in the penultimate position
	ramInGbOneDecimal.insert(ramInGbOneDecimal.length() - 1, ".");
	m_ram = ramInGbOneDecimal + "Gb";

	LPDIRECT3D9 pD3D = nullptr;
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DADAPTER_IDENTIFIER9 adapterIdentifier;
	pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapterIdentifier);

	std::string gpuVendor = std::to_string(adapterIdentifier.VendorId);
	std::string gpuDevice = std::to_string(adapterIdentifier.DeviceId);
	m_gpuVendorAndDevice = "vendor " + gpuVendor + " device " + gpuDevice;
	m_gpuBrand = adapterIdentifier.Description;
}

std::string WindowHardware::FormatVersion(unsigned int i_major, unsigned int i_minor, unsigned int i_patch)
{
	return std::to_string(i_major) + "." + std::to_string(i_minor) + "." + std::to_string(i_patch);;
}
