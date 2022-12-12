#include "GameObject.h"

void GameObject::AddComponent(ComponentType i_componentType)
{
	switch (i_componentType)
	{
	case ComponentType::Transform: //can't have multiple transforms
		break;
	default:
		break;
	}
}

const Component* GameObject::GetComponent(ComponentType i_componentType)
{
	for (std::list<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
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
