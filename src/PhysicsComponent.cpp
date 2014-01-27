#include "stdafx.h"
#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent(float speed) : speed_(speed){
}

void PhysicsComponent::update(int frameTime){
	velocity_ = getDirection() * speed_;
	parent_->move(getVelocity() * (float)frameTime);
}

sfld::Vector2f PhysicsComponent::getVelocity() const{
	return velocity_;
}

sfld::Vector2f PhysicsComponent::getDirection() const{
	return direction_;
}

void PhysicsComponent::setDirection(const sfld::Vector2f& unnormalisedVector){
	direction_ = unnormalisedVector.normalise();
}

void PhysicsComponent::setSpeed(float speed){
	speed_ = speed;
}
