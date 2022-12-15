#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"
#include "ModuleEditor.h"

#include "../External/SDL/include/SDL.h"
#include "imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	App->editor->OutputToConsole("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
        App->editor->OutputToConsole("SDL_EVENTS could not initialize! SDL_Error: "
                                     + std::string(SDL_GetError()) + "\n");
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    char* dropfileDir;
    bool mouseMotion = false;
    bool zoomChanged = false;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
                    return UPDATE_STOP;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    m_rightButtonPressed = true;
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    m_leftButtonPressed = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    m_rightButtonPressed = false;
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    m_leftButtonPressed = false;
                break;
            case SDL_MOUSEMOTION:
                mouseMotion = true;
                break;
            case SDL_MOUSEWHEEL:
                zoomChanged = true;
                break;
            case SDL_DROPFILE:
                dropfileDir = sdlEvent.drop.file;
                App->editor->OutputToConsole("File dropped: " + std::string(dropfileDir));
                App->renderer->SetModel3D(dropfileDir);
                break;
        }
    }

    m_keyboard = SDL_GetKeyboardState(NULL);
    int deltaTime = App->GetDeltaTime();

    if (App->editor->IsSceneFocused()) {
        if (m_rightButtonPressed) {
            //translate camera
            float3 deltaPosVec = float3::zero;
            float deltaPos = m_cameraSpeed * deltaTime;
            if (m_keyboard[SDL_SCANCODE_LSHIFT])
                deltaPos *= 2;

            if (m_keyboard[SDL_SCANCODE_W]) {
                deltaPosVec.x += deltaPos;
            }
            if (m_keyboard[SDL_SCANCODE_S]) {
                deltaPosVec.x -= deltaPos;
            }
            if (m_keyboard[SDL_SCANCODE_Q]) {
                deltaPosVec.y += deltaPos;
            }
            if (m_keyboard[SDL_SCANCODE_E]) {
                deltaPosVec.y -= deltaPos;
            }
            if (m_keyboard[SDL_SCANCODE_D]) {
                deltaPosVec.z += deltaPos;
            }
            if (m_keyboard[SDL_SCANCODE_A]) {
                deltaPosVec.z -= deltaPos;
            }
            App->camera->Translate(deltaPosVec);
        }

        if (mouseMotion) {
            //rotate camera
            float2 deltaRot = float2::zero;
            float deltaAngle = m_angleSpeed * deltaTime;
            deltaRot.x = -deltaAngle * sdlEvent.motion.xrel;
            deltaRot.y = -deltaAngle * sdlEvent.motion.yrel;
            if (m_rightButtonPressed) {
                App->camera->Rotate(deltaRot);
            }
            else if (m_leftButtonPressed && m_keyboard[SDL_SCANCODE_LALT]) {
                App->renderer->OrbitCameraAroundModel(deltaRot);
            }
        }

        if (zoomChanged) {
            bool zoomIncreased = sdlEvent.wheel.y >= 0;
            float deltaZoom = m_zoomSpeed * deltaTime;
            App->camera->Zoom(deltaZoom, zoomIncreased);
        }

        if (m_keyboard[SDL_SCANCODE_F])
            App->renderer->FocusCameraOnModel();
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    LOG_ENGINE("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
