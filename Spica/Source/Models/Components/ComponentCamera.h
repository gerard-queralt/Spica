#pragma once

#include "Models/Components/Component.h"

#include "Geometry/Frustum.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* i_gameObject);
	~ComponentCamera();

	ComponentType GetType() override {
		return ComponentType::Camera;
	}

	void Start() override;
	void Update() override;

	float4x4 GetProjection() {
		return m_frustum.ProjectionMatrix();
	}
	float4x4 GetView() {
		return m_frustum.ViewMatrix();
	}
	float3 GetFront() {
		return m_frustum.Front();
	}
	float3 GetUp() {
		return m_frustum.Up();
	}
	float3 GetWorldRight() {
		return m_frustum.WorldRight();
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

	void LookAt(const float3& i_pointToFocus);
	void Orbit(const float3& i_pointToOrbit, const float2& i_thetasRad);
	void Zoom(float i_deltaZoom, bool i_increaseZoom);

	//TMP
	void UpdateRotationWithTransform();

private:
	void UpdateFrustrumWithTransform();

	Frustum m_frustum;
};

