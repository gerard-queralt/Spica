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
	float3x3 rotationX = float3x3::RotateY(i_thetasRad.x);
	float3x3 rotationY = float3x3::RotateAxisAngle(GetWorldRight(), i_thetasRad.y);

	float3x3 rotationMat = rotationX * rotationY;

	float3 oldUp = GetUp().Normalized();
	float3 newUp = rotationMat.MulDir(oldUp);

	if (newUp.y < 0.f) {
		rotationMat = rotationX;
	}

	GetParent()->m_transform->SetRotation(rotationMat);

	float3 oldFront = m_frustum.Front().Normalized();
	float distanceToPoint = i_pointToOrbit.Distance(m_frustum.Pos());

	float3 newPos = i_pointToOrbit - oldFront * distanceToPoint;

	GetParent()->m_transform->SetPosition(newPos);
}

void ComponentCamera::Zoom(float i_deltaZoom, bool i_increaseZoom)
{
	if (i_increaseZoom)
		i_deltaZoom *= -1;
	this->GetParent()->m_transform->Translate(float3(0.f, 0.f, i_deltaZoom));
}

void ComponentCamera::UpdateFrustrumWithTransform()
{
	ComponentTransform* parentTransform = this->GetParent()->m_transform;
	m_frustum.SetPos(parentTransform->GetPosition());

	float3x3 rotationMatrix = float3x3::FromQuat(parentTransform->GetRotation());
	float3 oldFront = m_frustum.Front().Normalized();
	float3 oldUp = m_frustum.Up().Normalized();
	m_frustum.SetFront(rotationMatrix.MulDir(oldFront));
	m_frustum.SetUp(rotationMatrix.MulDir(oldUp));
	//reset rotation so it doesn't apply each frame
	parentTransform->SetRotation(float3x3::identity);
}
