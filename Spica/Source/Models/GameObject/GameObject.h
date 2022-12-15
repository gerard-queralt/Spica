#pragma once

#include <vector>
#include <string>

#include "Models/Components/Component.h"
#include "Models/Components/ComponentTransform.h"

class GameObject
{
public:
	GameObject(const std::string& i_name) {
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

	std::string m_name;
	ComponentTransform* m_transform;

private:
	std::vector<Component*> m_components;
};

