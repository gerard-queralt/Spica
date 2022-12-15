#pragma once

#include "Module.h"
#include "Models/Components/ComponentCamera.h"

class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();

	bool Init() override;
	update_status Update() override;

	inline const float4x4& GetProjection() const {
		return m_camera->GetProjection();
	}
	inline const float4x4& GetView() const {
		return m_camera->GetView();
	}
	inline float GetFOVrads() const {
		return m_camera->GetFOVrads();
	}
	inline float GetFOVdeg() const {
		return m_camera->GetFOVdeg();
	}
	inline float GetNearPlaneDistance() const {
		return m_camera->GetNearPlaneDistance();
	}
	inline float GetFarPlaneDistance() const {
		return m_camera->GetFarPlaneDistance();
	}

	inline void SetFOVrads(float i_rads) {
		m_camera->SetFOVrads(i_rads);
	}
	inline void SetFOVdeg(float i_deg) {
		m_camera->SetFOVdeg(i_deg);
	}
	inline void SetAspectRatio(float i_ratio) {
		m_camera->SetAspectRatio(i_ratio);
	}
	inline void SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance) {
		m_camera->SetPlaneDistances(i_nearPlaneDistance, i_farPlaneDistance);
	}
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

