#pragma once

#include "Globals.h"
#include <string>

class Window
{
public:
	~Window() {}

	virtual void Draw(bool& i_enabled) = 0;

	std::string GetName() {
		return m_name;
	}
	
protected:
	Window(const std::string& i_name) {
		m_name = i_name;
	}

	std::string m_name;
};

