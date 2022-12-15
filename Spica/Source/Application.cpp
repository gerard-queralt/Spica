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
	m_modules.push_back(editor = std::make_shared<ModuleEditor>());
	m_modules.push_back(window = std::make_shared<ModuleWindow>());
	m_modules.push_back(renderer = std::make_shared<ModuleRender>());
	m_modules.push_back(input = std::make_shared<ModuleInput>());
	m_modules.push_back(program = std::make_shared<ModuleProgram>());
	m_modules.push_back(camera = std::make_shared<ModuleEditorCamera>());
	m_modules.push_back(debugDraw = std::make_shared<ModuleDebugDraw>());
	m_modules.push_back(texture = std::make_shared<ModuleTexture>());
	
	m_timer = std::make_unique<MillisecondTimer>();
}

Application::~Application()
{
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

	for(vector<std::shared_ptr<Module>>::reverse_iterator it = m_modules.rbegin();
		it != m_modules.rend() && ret;
		++it)
		ret = (*it)->CleanUp();

	return ret;
}
