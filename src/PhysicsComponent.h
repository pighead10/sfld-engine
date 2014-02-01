//PhysicsComponent
//handles movement and collisions

#pragma once

#include "Component.h"
#include "Vector.h"
#include "OrientedRectangle.h"

class CollisionGrid;

class PhysicsComponent : public Component{
public:
	explicit PhysicsComponent(float speed,CollisionGrid* collisionGrid);
	~PhysicsComponent();

	void update(int frameTime);

	sfld::Vector2f getVelocity() const;
	sfld::Vector2f getDirection() const;

	void setDirection(const sfld::Vector2f& unnormalisedVector);
	void setSpeed(float speed);

	bool isWithinCollisionRange(GameObject* object); //uses manhattan 
	void moveWithCollisions(int frameTime);
	void collided(GameObject* other);

	FloatOrientedRect getOrientedBoundings();

	void moveOnGrid(const sfld::Vector2f& position); //should NOT be called from this function
private:
	std::vector<GameObject*> doneCollisions_;
	CollisionGrid* collisionGrid_;
	sfld::Vector2f direction_;
	sfld::Vector2f velocity_;
	float speed_;
};