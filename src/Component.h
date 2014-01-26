#pragma once

#include "stdafx.h"
#include "GameObject.h"

class ComponentMessage;

class Component : public sf::NonCopyable{
	friend GameObject::GameObject(GameObject&& other);
	friend void GameObject::addComponent(Component* component);
public:
	Component() = default;
	virtual ~Component() = default;

	virtual void update(int frameTime) = 0;
	virtual void receive(const ComponentMessage& message){}
protected:
	GameObject* parent_;
};