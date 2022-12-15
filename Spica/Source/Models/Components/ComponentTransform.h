#pragma once

#include "Models/Components/Component.h"

#include "Math/float3.h"
#include "Math/Quat.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* i_gameObject);
	~ComponentTransform();

	inline ComponentType GetType() const override {
		return ComponentType::Transform;
	}

	inline const float3& GetPosition() const {
		return m_position;
	}
	inline const Quat& GetRotation() const {
		return m_rotation;
	}
	inline const float3& GetScale() const {
		return m_scale;
	}

	void SetPosition(const float3& i_position);
	void SetPosition(float i_posX, float i_posY, float i_posZ);

	void SetRotation(const Quat& i_quaternion);
	void SetRotation(const float3x3& i_rotationMat);
	void SetRotation(const float3& i_rotation);
	void SetRotation(float i_radsX, float i_radsY, float i_radsZ);

	void SetScale(const float3& i_scale);
	void SetScale(float i_scaleX, float i_scaleY, float i_scaleZ);

	void Translate(const float4x4& i_translationMatrix);
	void Translate(const float3& i_deltaCoords);
	void Translate(float i_deltaX, float i_deltaY, float i_deltaZ);

	void Rotate(const float4x4& i_rotationMatrix);
	void Rotate(const float3& i_thetasRad);
	void Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad);

	void Scale(const float4x4& i_scaleMatrix);
	void Scale(const float3& i_deltaScale);
	void Scale(float i_scaleX, float i_scaleY, float i_scaleZ);

private:
	const float4x4& ComputeTranslationMatrix(const float3& i_deltaCoords) const;
	const float4x4& ComputeRotationMatrix(const float3& i_thetasRad) const;
	const float4x4& ComputeScaleMatrix(const float3& i_deltaScale) const;
	
	float3 m_position = float3::zero;
	Quat m_rotation = Quat::identity;
	float3 m_scale = float3::one;
};

