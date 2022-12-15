#include "GameObject.h"

#include "Models/Components/ComponentCamera.h"

void GameObject::Init()
{
	for (std::list<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
		(*it)->Init();
	}
}

void GameObject::Start()
{
	for (std::list<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
		(*it)->Start();
	}
}

void GameObject::Update()
{
	for (std::list<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
		(*it)->Update();
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
	for (std::list<Component*>::const_iterator it = m_components.begin(); it != m_components.end(); ++it) {
		if ((*it)->GetType() == i_componentType)
			return (*it);
	}
}

void GameObject::RemoveComponent(ComponentType i_componentType)
{
	for (std::list<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
		if ((*it)->GetType() == i_componentType) {
			delete (*it);
			return;
		}
	}
}
