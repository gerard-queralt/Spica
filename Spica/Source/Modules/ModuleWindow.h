#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "../External/SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

	inline void ResizeWindow(int i_width, int i_height) {
		SDL_SetWindowSize(m_window, i_width, i_height);
	}
	
	inline bool IsWindowFullscreen() const {
		return IsFlagSet(SDL_WINDOW_FULLSCREEN) && m_fullscreen;
	}
	inline bool IsWindowResizable() const {
		return IsFlagSet(SDL_WINDOW_RESIZABLE);
	}
	inline bool IsWindowBorderless() const {
		return IsFlagSet(SDL_WINDOW_BORDERLESS);
	}
	inline bool IsWindowDesktopFullscreen() const {
		return IsFlagSet(SDL_WINDOW_FULLSCREEN_DESKTOP) && !m_fullscreen;
	}
	inline float GetWindowBrightness() const {
		return SDL_GetWindowBrightness(m_window);
	}

	void SetWindowToDefault();
	void SetFullscreen(bool i_fullscreen);
	void SetResizable(bool i_resizable);
	void SetBorderless(bool i_borderless);
	void SetDesktopFullscreen(bool i_fullDesktop);
	void SetWindowBrightness(float i_brightness);

public:
	//The window we'll be rendering to
	SDL_Window* m_window = NULL;

	//The surface contained by the window
	SDL_Surface* m_screenSurface = NULL;

private:
	SDL_bool BoolToSDL_Bool(bool i_bool);
	inline bool IsFlagSet(SDL_WindowFlags i_flag) const {
		Uint32 windowFlags = SDL_GetWindowFlags(m_window);
		return windowFlags & i_flag;
	}

	//whether the window was set to regular fullscreen (true) or desktop fullscreen (false)
	//this is because both flags are set at the same time, so it's impossible to differentiate otherwise
	bool m_fullscreen = false;
};

#endif // __ModuleWindow_H__