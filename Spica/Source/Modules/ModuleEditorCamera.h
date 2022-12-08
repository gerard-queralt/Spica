#pragma once

#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();

	bool Start();

	float4x4 GetProjection() {
		return m_frustum.ProjectionMatrix();
	}
	float4x4 GetView() {
		return m_frustum.ViewMatrix();
	}
	float GetFOVrads() {
		return m_frustum.HorizontalFov();
	}
	float GetFOVdeg() {
		return GetFOVrads() * (180.f / math::pi);
	}
	float GetNearPlaneDistance() {
		return m_frustum.NearPlaneDistance();
	}
	float GetFarPlaneDistance() {
		return m_frustum.FarPlaneDistance();
	}

	void SetFOVrads(float i_rads);
	void SetFOVdeg(float i_deg);
	void SetAspectRatio(float i_ratio);
	void SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance);
	void SetPosition(const float3& i_pos);
	void SetPosition(float i_x, float i_y, float i_z);
	void SetOrientation(const float3& i_ori);
	void SetOrientation(float i_x, float i_y, float i_z);
	void SetLookAt(const float3& i_lookAt);
	void SetLookAt(float i_x, float i_y, float i_z);
	
	void Translate(const float3& i_deltaCoords);
	void Translate(float i_deltaX, float i_deltaY, float i_deltaZ);
	
	void Rotate(const float3x3& i_rotationMatrix);
	void Rotate(const float3& i_thetasRad);
	void Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad);

	void FocusOn(const float3& i_pointToFocus);
	void Orbit(const float3& i_pointToOrbit, const float3& i_thetasRad);
	void Zoom(float i_deltaZoom, bool i_increaseZoom);

private:
	Frustum m_frustum;
};

