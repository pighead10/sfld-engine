#pragma once

#include "stdafx.h"

class Component;
class GameObjectManager;

class GameObject : public sf::NonCopyable{
public:
	GameObject(GameObject&&) = default;
	void addComponent(Component* component);
	void update(int frameTime);
	
private:
	int id;
	sf::Vector2f position_;
	std::vector<std::unique_ptr<Component>> components_;
};