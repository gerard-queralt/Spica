#pragma once

enum class ComponentType
{
	Transform,
	Camera
};

class GameObject;

class Component
{
public:
	Component(GameObject* i_gameObject) {
		m_gameObject = i_gameObject;
	}
	~Component() {}

	virtual ComponentType GetType() = 0;
	GameObject* GetParent() {
		return m_gameObject;
	}

	virtual void Init() {}
	virtual void Start() {}
	virtual void Update() {}

private:
	GameObject* m_gameObject;
};
