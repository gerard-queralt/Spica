#include "ComponentTransform.h"

#include "Math/float3x3.h"
#include "Math/float3x4.h"
#include "Math/float4x4.h"

ComponentTransform::ComponentTransform(GameObject* i_gameObject) : Component(i_gameObject)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::SetPosition(const float3& i_position)
{
	m_position = i_position;
}

void ComponentTransform::SetPosition(float i_posX, float i_posY, float i_posZ)
{
	float3 posAsVec = float3(i_posX, i_posY, i_posZ);
	SetPosition(posAsVec);
}

void ComponentTransform::SetRotation(const Quat& i_quaternion)
{
	m_rotation = i_quaternion;
}

void ComponentTransform::SetRotation(const float3x3& i_rotationMat)
{
	Quat quaternion(i_rotationMat);
	SetRotation(quaternion);
}

void ComponentTransform::SetRotation(const float3& i_rotation)
{
	float3x3 rotationMat = ComputeRotationMatrix(i_rotation).Float3x3Part();
	SetRotation(rotationMat);
}

void ComponentTransform::SetRotation(float i_radsX, float i_radsY, float i_radsZ)
{
	float3 radsAsVec = float3(i_radsX, i_radsY, i_radsZ);
	SetRotation(radsAsVec);
}

void ComponentTransform::SetScale(const float3& i_scale)
{
	m_scale = i_scale;
}

void ComponentTransform::SetScale(float i_scaleX, float i_scaleY, float i_scaleZ)
{
	float3 scaleAsVec = float3(i_scaleX, i_scaleY, i_scaleZ);
	SetScale(scaleAsVec);
}

void ComponentTransform::Translate(const float4x4& i_translationMatrix)
{
	float3 newPos = (i_translationMatrix * float4(m_position, 1.0f)).xyz();
	m_position = newPos;
}

void ComponentTransform::Translate(const float3& i_deltaCoords)
{
	float4x4 translationMat = ComputeTranslationMatrix(i_deltaCoords);
	Translate(translationMat);
}

void ComponentTransform::Translate(float i_deltaX, float i_deltaY, float i_deltaZ)
{
	Translate(float3(i_deltaX, i_deltaY, i_deltaZ));
}

void ComponentTransform::Rotate(const float4x4& i_rotationMatrix)
{
	float4x4 orthonormalMat = i_rotationMatrix;
	orthonormalMat.Orthonormalize3();
	Quat newRotation = m_rotation * Quat(orthonormalMat);
	m_rotation = newRotation;
}

void ComponentTransform::Rotate(const float3& i_thetasRad)
{
	float4x4 rotationMat = ComputeRotationMatrix(i_thetasRad);
	Rotate(rotationMat);
}

void ComponentTransform::Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad)
{
	Rotate(float3(i_thetaXRad, i_thetaYRad, i_thetaZRad));
}

void ComponentTransform::Scale(const float4x4& i_scaleMatrix)
{
	float3 newScale = i_scaleMatrix.Float3x3Part() * m_scale;
	m_scale = newScale;
}

void ComponentTransform::Scale(const float3& i_deltaScale)
{
	float4x4 scaleMat = ComputeScaleMatrix(i_deltaScale);
	Scale(scaleMat);
}

void ComponentTransform::Scale(float i_scaleX, float i_scaleY, float i_scaleZ)
{
	Scale(float3(i_scaleX, i_scaleY, i_scaleZ));
}

float4x4 ComponentTransform::ComputeTranslationMatrix(const float3& i_deltaCoords)
{
	float4x4 translationMat = float4x4(float3x4(float3x3::identity, i_deltaCoords));

	return translationMat;
}

float4x4 ComponentTransform::ComputeRotationMatrix(const float3& i_thetasRad)
{
	float3x3 rotationX = float3x3::RotateY(i_thetasRad.x);
	float3x3 rotationY = float3x3::RotateX(i_thetasRad.y);
	float3x3 rotationZ = float3x3::RotateZ(i_thetasRad.z);

	float3x3 rotationMat = rotationX * rotationY * rotationZ;

	return float4x4(rotationMat);
}

float4x4 ComponentTransform::ComputeScaleMatrix(const float3& i_deltaScale)
{
	float3x3 scaleMatrix = float3x3(float3(i_deltaScale.x, 0.f, 0.f),
		float3(0.f, i_deltaScale.y, 0.f),
		float3(0.f, 0.f, i_deltaScale.z));

	return float4x4(scaleMatrix);
}
