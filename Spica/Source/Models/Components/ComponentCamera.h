#pragma once

#include "Models/Components/Component.h"

#include "Geometry/Frustum.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* i_gameObject);
	~ComponentCamera();

	inline ComponentType GetType() const override {
		return ComponentType::Camera;
	}

	void Start() override;
	void Update() override;

	inline const float4x4& GetProjection() const {
		return m_frustum.ProjectionMatrix();
	}
	inline const float4x4& GetView() const {
		return m_frustum.ViewMatrix();
	}
	inline const float3& GetFront() const {
		return m_frustum.Front();
	}
	inline const float3& GetUp() const {
		return m_frustum.Up();
	}
	inline const float3& GetWorldRight() const {
		return m_frustum.WorldRight();
	}
	float GetFOVrads() const {
		return m_frustum.HorizontalFov();
	}
	float GetFOVdeg() const {
		return GetFOVrads() * (180.f / math::pi);
	}
	float GetNearPlaneDistance() const {
		return m_frustum.NearPlaneDistance();
	}
	float GetFarPlaneDistance() const {
		return m_frustum.FarPlaneDistance();
	}

	void SetFOVrads(float i_rads);
	void SetFOVdeg(float i_deg);
	void SetAspectRatio(float i_ratio);
	void SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance);

	void LookAt(const float3& i_pointToFocus);
	void Orbit(const float3& i_pointToOrbit, const float2& i_thetasRad);
	void Zoom(float i_deltaZoom, bool i_increaseZoom);

private:
	void UpdateFrustrumWithTransform();

	Frustum m_frustum;
};

