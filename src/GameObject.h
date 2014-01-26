#pragma once

#include "stdafx.h"

class Component;
class GameObjectManager;
class ComponentMessage;

typedef std::vector<std::unique_ptr<Component>> ComponentPtrVector;

class GameObject : public sf::NonCopyable{
public:
	GameObject();
	GameObject(GameObject&& other);

	void send(const ComponentMessage& message);
	void addComponent(Component* component);
	void update(int frameTime);
	sfld::Vector2f getPosition() const;
private:
	int id_;
	sfld::Vector2f position_;
	ComponentPtrVector components_;
};