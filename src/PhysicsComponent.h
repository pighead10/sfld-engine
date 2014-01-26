//PhysicsComponent
//handles movement and collisions

#pragma once

#include "Component.h"
#include "Vector.h"

class PhysicsComponent : public Component{
public:
	explicit PhysicsComponent(int speed);

	void update(int frameTime);

	sfld::Vector2f getVelocity() const;
	sfld::Vector2f getDirection() const;

	void setDirection(const sfld::Vector2f& unnormalisedVector);
	void setSpeed(int speed);
private:
	sfld::Vector2f direction_;
	sfld::Vector2f velocity_;
	int speed_;
};