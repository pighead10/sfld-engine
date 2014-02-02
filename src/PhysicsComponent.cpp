#include "stdafx.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "OrientedRectangle.h"
#include "GameObjectManager.h"
#include "CollisionGrid.h"
#include "ComponentMessage.h"

PhysicsComponent::PhysicsComponent(float speed, CollisionGrid* collisionGrid)
	: speed_(speed), collisionGrid_(collisionGrid) {
}

PhysicsComponent::~PhysicsComponent(){
	collisionGrid_->remove(parent_->getPosition(), this);
}

void PhysicsComponent::update(int frameTime){
	velocity_ = getDirection() * speed_;
	moveWithCollisions(frameTime);
}

sfld::Vector2f PhysicsComponent::getVelocity() const{
	return velocity_;
}

sfld::Vector2f PhysicsComponent::getDirection() const{
	return direction_;
}

void PhysicsComponent::moveOnGrid(const sfld::Vector2f& position){ //should not be called by PhysicsComponent
	collisionGrid_->move(parent_->getPosition(), position, this);
}

void PhysicsComponent::addToGrid(const sfld::Vector2f& position){ //should not be called by PhysicsComponent
	collisionGrid_->add(position, this);
}

bool PhysicsComponent::isWithinCollisionRange(GameObject* object){
	sfld::Vector2f size1 = parent_->getSize();
	sfld::Vector2f size2 = object->getSize();

	float maxsize1 = std::max(size1.x, size1.y);
	float maxsize2 = std::max(size2.x, size2.y);

	sfld::Vector2f pos1 = parent_->getPosition();
	sfld::Vector2f pos2 = object->getPosition();

	float maxlength = maxsize1 + maxsize2;
	float distance = abs(pos1.x - pos2.x) - abs(pos1.x - pos2.x);
	
	if (distance <= maxlength){
		if (distance * distance <= maxlength * maxlength){
			return true;
		}
	}
	return false;
}

FloatOrientedRect PhysicsComponent::getOrientedBoundings(){
	return FloatOrientedRect(parent_->getBoundings(), parent_->getOrigin(), parent_->getRotation());
}

void PhysicsComponent::collided(GameObject* other){
	//check if collision has already been resolved this frame
	std::vector<GameObject*>::iterator it;
	for (it = doneCollisions_.begin(); it != doneCollisions_.end(); it++){
		if (*it == other){
			return;
		}
	}

	MessageInfo info;
	info["object"] = other;
	parent_->send(ComponentMessage(ComponentMessage::CATEGORY_PHYSICS, ComponentMessage::PHYSICS_COLLISION, info));
	doneCollisions_.push_back(other);
}

void PhysicsComponent::moveWithCollisions(int frameTime){
	sfld::Vector2f movement = getVelocity() * (float)frameTime;
	sfld::Vector2f newPos = parent_->getPosition() + movement;

	sf::FloatRect boundings = parent_->getBoundings();
	boundings.left = newPos.x;
	boundings.top = newPos.y;

	FloatOrientedRect orientedBoundings = getOrientedBoundings();
	PhysicsContainer potentialCollisions = collisionGrid_->getPotentialCollisions(orientedBoundings);
	PhysicsContainer::iterator it;
	for (it = potentialCollisions.begin(); it != potentialCollisions.end(); it++){
		if (*it != this){
			sfld::Vector2f mtv = orientedBoundings.checkForSATCollision((*it)->getOrientedBoundings());
			if (mtv != sfld::Vector2f(0, 0)){
				//collision

				//hack
				if (movement != sfld::Vector2f(0, 0)){
					newPos -= mtv;
				}

				(*it)->collided(parent_);
				collided((*it)->parent_);
			}
		}
	}

	parent_->setPosition(newPos);
}



void PhysicsComponent::setDirection(const sfld::Vector2f& unnormalisedVector){
	direction_ = unnormalisedVector.normalise();
}


void PhysicsComponent::setSpeed(float speed){
	speed_ = speed;
}
