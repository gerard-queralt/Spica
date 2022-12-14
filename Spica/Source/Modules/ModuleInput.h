#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	friend class WindowInput;

	const Uint8* m_keyboard = NULL;

	bool m_rightButtonPressed = false;
	bool m_leftButtonPressed = false;
	float m_cameraSpeed = 0.02f;
	float m_angleSpeed = 0.0005f;
	float m_zoomSpeed = 0.005f;
};