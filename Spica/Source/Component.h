#pragma once

enum class ComponentType
{
	Transform
};

class GameObject;

class Component
{
public:
	Component(const GameObject* i_gameObject) {
		m_gameObject = i_gameObject;
	}
	~Component() {}

	virtual ComponentType GetType() = 0;
	const GameObject* GetParent() {
		return m_gameObject;
	}

private:
	const GameObject* m_gameObject;
};
