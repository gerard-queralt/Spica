#pragma once

#include "Module.h"

#include <list>

#include "Models/Windows/WindowMainMenu.h"
#include "Models/Windows/EditorWindows/EditorWindow.h"
#include "Models/Windows/EditorWindows/WindowConsole.h"
#include "Models/Windows/EditorWindows/WindowModel3D.h"
#include "Models/Windows/EditorWindows/WindowScene.h"
#include "Models/3DModels/Model3D.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void OutputToConsole(const std::string& i_textToPrint);
	void SetTargetModel(const Model3D* i_model);
	inline bool IsSceneFocused() const {
		return m_scene->IsFocused();
	}

private:
	std::list<EditorWindow*> m_windows;
	WindowMainMenu* m_mainMenu = nullptr;
	WindowConsole* m_console = nullptr;
	WindowModel3D* m_model = nullptr;
	WindowScene* m_scene = nullptr;
};

