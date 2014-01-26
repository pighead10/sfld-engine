#include "stdafx.h"
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int speed) : speed_(speed){
}

void PhysicsComponent::update(int frameTime){
	//update..
}

sfld::Vector2f PhysicsComponent::getVelocity() const{
	return velocity_;
}

sfld::Vector2f PhysicsComponent::getDirection() const{
	return direction_;
}

