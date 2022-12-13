#include "ComponentCamera.h"

#include "Models/GameObject/GameObject.h"
#include "Models/Components/ComponentTransform.h"

#include "Math/float3x3.h"

ComponentCamera::ComponentCamera(GameObject* i_gameObject) : Component(i_gameObject)
{
	m_frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	m_frustum.SetFront(-float3::unitZ);
	m_frustum.SetUp(float3::unitY);
}

ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::Start()
{
	UpdateFrustrumWithTransform();
}

void ComponentCamera::Update()
{
	UpdateFrustrumWithTransform();
}

void ComponentCamera::SetFOVrads(float i_rads)
{
	m_frustum.SetHorizontalFovAndAspectRatio(i_rads, m_frustum.AspectRatio());
}

void ComponentCamera::SetFOVdeg(float i_deg)
{
	SetFOVrads((math::pi / 180.0f) * i_deg);
}

void ComponentCamera::SetAspectRatio(float i_ratio)
{
	m_frustum.SetHorizontalFovAndAspectRatio(m_frustum.HorizontalFov(), i_ratio);
}

void ComponentCamera::SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance)
{
	m_frustum.SetViewPlaneDistances(i_nearPlaneDistance, i_farPlaneDistance);
}

void ComponentCamera::LookAt(const float3& i_pointToFocus)
{
	float3 direction = i_pointToFocus - m_frustum.Pos();

	float3x3 rotMat =
		float3x3::LookAt(m_frustum.Front().Normalized(), direction.Normalized(), m_frustum.Up().Normalized(), float3::unitY);

	float3 oldFront = m_frustum.Front().Normalized();
	m_frustum.SetFront(rotMat.MulDir(oldFront));

	float3 oldUp = m_frustum.Up().Normalized();
	m_frustum.SetUp(rotMat.MulDir(oldUp));
}

void ComponentCamera::Orbit(const float3& i_pointToOrbit, const float2& i_thetasRad)
{
	this->GetParent()->m_transform->SetRotation(float3(i_thetasRad, 0.f));
	this->UpdateRotationWithTransform();

	float3 oldFront = m_frustum.Front().Normalized();
	float distanceToPoint = i_pointToOrbit.Distance(m_frustum.Pos());

	float3 newPos = i_pointToOrbit - oldFront * distanceToPoint;

	this->GetParent()->m_transform->Translate(newPos);
}

void ComponentCamera::Zoom(float i_deltaZoom, bool i_increaseZoom)
{
	if (!i_increaseZoom)
		i_deltaZoom *= -1;
	this->GetParent()->m_transform->Translate(float3(i_deltaZoom, 0.f, 0.f));
}

void ComponentCamera::UpdateRotationWithTransform()
{
	ComponentTransform* parentTransform = this->GetParent()->m_transform;
	float3x3 rotationMatrix = float3x3::FromQuat(parentTransform->GetRotation());
	float3 oldFront = m_frustum.Front().Normalized();
	float3 oldUp = m_frustum.Up().Normalized();
	m_frustum.SetFront(rotationMatrix.MulDir(oldFront));
	m_frustum.SetUp(rotationMatrix.MulDir(oldUp));
}

void ComponentCamera::UpdateFrustrumWithTransform()
{
	ComponentTransform* parentTransform = this->GetParent()->m_transform;
	m_frustum.SetPos(parentTransform->GetPosition());
}
