#include "ModuleEditorCamera.h"

#include "SDL.h"
#include "Math/float3x3.h"

#include "Application.h"
#include "Modules/ModuleWindow.h"
#include "Models/GameObject/GameObject.h"

ModuleEditorCamera::ModuleEditorCamera()
{
}

ModuleEditorCamera::~ModuleEditorCamera()
{
}

bool ModuleEditorCamera::Init()
{
	GameObject* cameraParent = new GameObject("Camera");
	cameraParent->AddComponent(ComponentType::Camera);
	m_camera = (ComponentCamera*)cameraParent->GetComponent(ComponentType::Camera);
	
	SetPosition(float3(0.0f, 3.0f, 5.0f));
	SetPlaneDistances(0.1f, 100.0f);

	int w, h;
	SDL_GetWindowSize(App->window->m_window, &w, &h);
	SetAspectRatio(((float)w) / ((float)h));
	SetFOVdeg(90.0f);

	//TMP
	m_camera->Start();

	return true;
}

update_status ModuleEditorCamera::Update()
{
	m_camera->GetParent()->Update();
	return UPDATE_CONTINUE;
}

float4x4 ModuleEditorCamera::GetProjection()
{
	return m_camera->GetProjection();
}

float4x4 ModuleEditorCamera::GetView()
{
	return m_camera->GetView();
}

float ModuleEditorCamera::GetFOVrads()
{
	return m_camera->GetFOVrads();
}

float ModuleEditorCamera::GetFOVdeg()
{
	return m_camera->GetFOVdeg();
}

float ModuleEditorCamera::GetNearPlaneDistance()
{
	return m_camera->GetNearPlaneDistance();
}

float ModuleEditorCamera::GetFarPlaneDistance()
{
	return m_camera->GetFarPlaneDistance();
}

void ModuleEditorCamera::SetFOVrads(float i_rads)
{
	m_camera->SetFOVrads(i_rads);
}

void ModuleEditorCamera::SetFOVdeg(float i_deg)
{
	m_camera->SetFOVdeg(i_deg);
}

void ModuleEditorCamera::SetAspectRatio(float i_ratio)
{
	m_camera->SetAspectRatio(i_ratio);
}

void ModuleEditorCamera::SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance)
{
	m_camera->SetPlaneDistances(i_nearPlaneDistance, i_farPlaneDistance);
}

void ModuleEditorCamera::SetPosition(const float3& i_pos)
{
	m_camera->GetParent()->m_transform->SetPosition(i_pos);
}

void ModuleEditorCamera::SetPosition(float i_x, float i_y, float i_z)
{
	SetPosition(float3(i_x, i_y, i_z));
}

void ModuleEditorCamera::SetOrientation(const float3& i_ori)
{
	m_camera->GetParent()->m_transform->SetRotation(i_ori);
}

void ModuleEditorCamera::SetOrientation(float i_x, float i_y, float i_z)
{
	SetOrientation(float3(i_x, i_y, i_z));
}

void ModuleEditorCamera::Translate(const float3& i_deltaCoords)
{
	float3 relativeCoords = float3::zero;
	relativeCoords += m_camera->GetFront().Normalized() * i_deltaCoords.x;
	relativeCoords += float3::unitY * i_deltaCoords.y;
	relativeCoords += m_camera->GetWorldRight().Normalized() * i_deltaCoords.z;

	m_camera->GetParent()->m_transform->Translate(relativeCoords);
}

void ModuleEditorCamera::Translate(float i_deltaX, float i_deltaY, float i_deltaZ)
{
	Translate(float3(i_deltaX, i_deltaY, i_deltaZ));
}

void ModuleEditorCamera::Rotate(const float2& i_thetasRad)
{
	float3x3 rotationX = float3x3::RotateY(i_thetasRad.x);
	float3x3 rotationY = float3x3::RotateAxisAngle(m_camera->GetWorldRight(), i_thetasRad.y);

	float3x3 rotationMat = rotationX * rotationY;

	float3 oldUp = m_camera->GetUp().Normalized();
	float3 newUp = rotationMat.MulDir(oldUp);

	if (newUp.y < 0.f) {
		rotationMat = rotationX;
	}

	m_camera->GetParent()->m_transform->SetRotation(rotationMat);
	m_camera->UpdateRotationWithTransform();
}

void ModuleEditorCamera::Rotate(float i_thetaXRad, float i_thetaYRad)
{
	Rotate(float2(i_thetaXRad, i_thetaYRad));
}

void ModuleEditorCamera::LookAt(const float3& i_pointToFocus)
{
	m_camera->LookAt(i_pointToFocus);
}

void ModuleEditorCamera::Orbit(const float3& i_pointToOrbit, const float2& i_thetasRad)
{
	Rotate(i_thetasRad);

	float3 oldFront = m_camera->m_frustum.Front().Normalized();
	float distanceToPoint = i_pointToOrbit.Distance(m_camera->m_frustum.Pos());

	float3 newPos = i_pointToOrbit - oldFront * distanceToPoint;

	m_camera->m_frustum.SetPos(newPos);
}

void ModuleEditorCamera::Zoom(float i_deltaZoom, bool i_increaseZoom)
{
	m_camera->Zoom(i_deltaZoom, i_increaseZoom);
}
