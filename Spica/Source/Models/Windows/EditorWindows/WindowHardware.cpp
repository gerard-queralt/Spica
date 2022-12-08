#include "WindowHardware.h"

#include <cmath>

#include "imgui.h"
#include "glew.h"
#include "SDL.h"
#include "d3d9.h"

WindowHardware::WindowHardware() : EditorWindow("Hardware")
{
	m_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	GetSoftwareVersions();
	GetCPUinfo();
	GetCaps();
	GetGPUinfo();
}

WindowHardware::~WindowHardware()
{
}

void WindowHardware::DrawWindowContents()
{

	ImGui::TextUnformatted(("glew Version: " + m_glewVersion).c_str());
	ImGui::TextUnformatted(("SDL Version: " + m_sdlVersion).c_str());

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
	char glewVersion[128];
	sprintf(glewVersion, "%s", glewGetString(GLEW_VERSION));
	m_glewVersion = std::string(glewVersion);

	m_sdlVersion = std::to_string(SDL_MAJOR_VERSION) + "." + std::to_string(SDL_MINOR_VERSION) + "." + std::to_string(SDL_PATCHLEVEL);
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
