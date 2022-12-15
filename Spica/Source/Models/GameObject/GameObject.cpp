#include "GameObject.h"

#include "Models/Components/ComponentCamera.h"

void GameObject::Init()
{
	for (Component* component : m_components) {
		component->Init();
	}
}

void GameObject::Start()
{
	for (Component* component : m_components) {
		component->Start();
	}
}

void GameObject::Update()
{
	for (Component* component : m_components) {
		component->Update();
	}
}

void GameObject::AddComponent(ComponentType i_componentType)
{
	switch (i_componentType)
	{
	case ComponentType::Transform: //can't have multiple transforms
		break;
	case ComponentType::Camera:
		m_components.push_back(new ComponentCamera(this));
		break;
	default:
		break;
	}
}

const Component* GameObject::GetComponent(ComponentType i_componentType) const
{
	for (Component* component : m_components) {
		if (component->GetType() == i_componentType)
			return component;
	}
	return nullptr;
}

void GameObject::RemoveComponent(ComponentType i_componentType)
{
	for (Component* component : m_components) {
		if (component->GetType() == i_componentType) {
			delete component;
			return;
		}
	}
}
