#pragma once

#include "stdafx.h"

class Component;
class GameObjectManager;
class ComponentMessage;
class PhysicsComponent;

typedef std::vector<std::unique_ptr<Component>> ComponentPtrVector;

class GameObject : public sf::NonCopyable{
public:	
	GameObject();
	GameObject(GameObject&& other);
	~GameObject();

	void send(const ComponentMessage& message);
	void addComponent(Component* component);
	void addPhysicsComponent(PhysicsComponent* component);
	void update(int frameTime);
	
	void move(const sfld::Vector2f& offset);

	void setPosition(const sfld::Vector2f& position);
	sfld::Vector2f getPosition() const;

	sfld::Vector2f getSize() const;
	void setSize(const sfld::Vector2f& size);

	sfld::Vector2f getOrigin() const;
	void setOrigin(const sfld::Vector2f& origin);

	float getRotation() const;
	void setRotation(float degrees);

	sf::FloatRect getBoundings() const;

	bool hasPhysics() const;
private:
	PhysicsComponent* physicsComponent_;

	float rotation_;
	int id_;
	sfld::Vector2f origin_;
	sfld::Vector2f size_;
	sfld::Vector2f position_;
	ComponentPtrVector components_;
};