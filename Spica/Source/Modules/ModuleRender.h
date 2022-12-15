#pragma once
#include "Module.h"
#include "Globals.h"

#include "glew.h"
#include "Math/float4x4.h"

#include "Models/3DModels/Model3D.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void UpdateBuffers(unsigned int i_width, unsigned int i_height);
	void SetModel3D(const char* i_modelPath);
	void FocusCameraOnModel();
	void OrbitCameraAroundModel(const float2& i_thetasRad);
	void SetShaders(const char* i_vertexShader, const char* i_fragmentShader);

	inline const float4x4& GetModel() const {
		return m_model;
	}
	inline GLuint GetProgram() const {
		return m_program;
	}
	inline const char* GetVertexShader() const {
		return m_vertexShader;
	}
	inline const char* GetFragmentShader() const {
		return m_fragmentShader;
	}

	GLuint m_framebuffer = 0;
	GLuint m_renderedTexture = 0;

private:
	friend class ModuleEditor;

	void UpdateProgram();

	void* m_context;

	GLuint m_depthrenderbuffer;
	GLuint m_program;
	Model3D* m_model3D;
	float4x4 m_model;
	const char* m_vertexShader = "default_vertex.glsl";
	const char* m_fragmentShader = "default_fragment.glsl";
};
