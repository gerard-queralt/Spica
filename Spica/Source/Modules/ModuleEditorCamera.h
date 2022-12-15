#pragma once

#include "Module.h"
#include "Models/Components/ComponentCamera.h"

class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();

	bool Init();
	update_status Update();

	float4x4 GetProjection();
	float4x4 GetView();
	float GetFOVrads();
	float GetFOVdeg();
	float GetNearPlaneDistance();
	float GetFarPlaneDistance();

	void SetFOVrads(float i_rads);
	void SetFOVdeg(float i_deg);
	void SetAspectRatio(float i_ratio);
	void SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance);
	void SetPosition(const float3& i_pos);
	void SetPosition(float i_x, float i_y, float i_z);
	void SetOrientation(const float3& i_ori);
	void SetOrientation(float i_x, float i_y, float i_z);
	
	void Translate(const float3& i_deltaCoords);
	void Translate(float i_deltaX, float i_deltaY, float i_deltaZ);
	
	void Rotate(const float2& i_thetasRad);
	void Rotate(float i_thetaXRad, float i_thetaYRad);

	void LookAt(const float3& i_pointToFocus);
	void Orbit(const float3& i_pointToOrbit, const float2& i_thetasRad);
	void Zoom(float i_deltaZoom, bool i_increaseZoom);

private:
	ComponentCamera* m_camera = nullptr;
};

