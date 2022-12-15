#pragma once

#include "EditorWindow.h"

#include <string>

class WindowHardware : public EditorWindow
{
public:
	WindowHardware();
	~WindowHardware();

protected:
	void DrawWindowContents() override;

private:
	void GetSoftwareVersions();
	void GetCPUinfo();
	void GetCaps();
	void GetGPUinfo();
	void UpdateAvailableMemory();

	const std::string& FormatVersion(unsigned int i_major, unsigned int i_minor, unsigned int i_patch) const;

	bool m_versionsSet = false;
	std::string m_glewVersion;
	std::string m_openGLVersion;
	std::string m_sdlVersion;
	std::string m_assimpVersion;
	std::string m_dirextXTexVersion;
	std::string m_imguiVersion;
	std::string m_mathGeoLibVersion;

	std::string m_cpusAndCache;
	std::string m_caps;

	std::string m_ram;
	std::string m_gpuVendorAndDevice;
	std::string m_gpuBrand;

	std::string m_availableRam;
	std::string m_totalRam;
	std::string m_usedRam;
};

