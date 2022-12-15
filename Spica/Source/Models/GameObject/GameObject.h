#pragma once

#include <list>

#include "Models/Components/Component.h"
#include "Models/Components/ComponentTransform.h"

class GameObject
{
public:
	GameObject(const char* i_name) {
		m_name = i_name;
		m_transform = new ComponentTransform(this);
		m_components.push_back(m_transform);
	}
	~GameObject() {}

	void Init();
	void Start();
	void Update();

	void AddComponent(ComponentType i_componentType);
	const Component* GetComponent(ComponentType i_componentType) const;
	void RemoveComponent(ComponentType i_componentType);

	const char* m_name;
	ComponentTransform* m_transform;

private:
	std::list<Component*> m_components;
};

