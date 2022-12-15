#pragma once
#include "Application.h"
#include "Modules/ModuleWindow.h"
#include "Modules/ModuleRender.h"
#include "Modules/ModuleInput.h"
#include "Modules/ModuleProgram.h"
#include "Modules/ModuleEditorCamera.h"
#include "Modules/ModuleEditor.h"
#include "Modules/ModuleDebugDraw.h"
#include "Modules/ModuleTexture.h"

#include "Models/Timers/MillisecondTimer.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	m_modules.push_back(editor = new ModuleEditor());
	m_modules.push_back(window = new ModuleWindow());
	m_modules.push_back(renderer = new ModuleRender());
	m_modules.push_back(input = new ModuleInput());
	m_modules.push_back(program = new ModuleProgram());
	m_modules.push_back(camera = new ModuleEditorCamera());
	m_modules.push_back(debugDraw = new ModuleDebugDraw());
	m_modules.push_back(texture = new ModuleTexture());
	
	m_timer = new MillisecondTimer();
}

Application::~Application()
{
	for(Module* module : m_modules)
    {
        delete module;
    }
	m_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	for(int i = 0; i < m_modules.size() && ret; ++i)
		ret = m_modules[i]->Init();

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (int i = 0; i < m_modules.size() && ret; ++i)
		ret = m_modules[i]->Start();

	m_timer->Start();
	m_prevTime = m_timer->Read();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	int currentTime = m_timer->Read();
	m_deltaTime = currentTime - m_prevTime;

	float timePerFrame = 0.f;
	if (0 < m_framesPerSecond)
		timePerFrame = 1000.f / m_framesPerSecond;

	if (timePerFrame < m_deltaTime){
		for (int i = 0; i < m_modules.size() && ret; ++i)
			ret = m_modules[i]->PreUpdate();

		for (int i = 0; i < m_modules.size() && ret; ++i)
			ret = m_modules[i]->Update();

		for (int i = 0; i < m_modules.size() && ret; ++i)
			ret = m_modules[i]->PostUpdate();

		m_prevTime = currentTime;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(vector<Module*>::reverse_iterator it = m_modules.rbegin(); it != m_modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
