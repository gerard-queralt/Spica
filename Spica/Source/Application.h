#pragma once

#include <memory>
#include <vector>

#include "Globals.h"
#include "Modules/Module.h"
#include "Models/Timers/MillisecondTimer.h"

class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleProgram;
class ModuleEditorCamera;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleTexture;
class Timer;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	std::shared_ptr<ModuleRender> renderer;
	std::shared_ptr<ModuleWindow> window;
	std::shared_ptr<ModuleInput> input;
	std::shared_ptr<ModuleProgram> program;
	std::shared_ptr<ModuleEditorCamera> camera;
	std::shared_ptr<ModuleEditor> editor;
	std::shared_ptr<ModuleDebugDraw> debugDraw;
	std::shared_ptr<ModuleTexture> texture;

	inline int GetDeltaTime() const {
		return m_deltaTime;
	}

	inline float GetFPS() const {
		return m_framesPerSecond;
	}

	inline void SetFPS(float i_framesPerSecond) {
		m_framesPerSecond = i_framesPerSecond;
	}

private:
	std::vector<std::shared_ptr<Module> > m_modules;

	float m_framesPerSecond = 60.f;

	std::unique_ptr<MillisecondTimer> m_timer;
	int m_prevTime = 0;
	int m_deltaTime = 0;
};

extern Application* App;
