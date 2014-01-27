#include "stdafx.h"
#include "SampleInputComponent.h"
#include "PhysicsComponent.h"

SampleInputComponent::SampleInputComponent(PhysicsComponent* physicsComponent)
	:physicsComponent_(physicsComponent){
}

void SampleInputComponent::update(int frameTime){
	using namespace sf;
	sfld::Vector2f direction; //not normalised
	if (Keyboard::isKeyPressed(Keyboard::W)) direction.y -= 1;
	if (Keyboard::isKeyPressed(Keyboard::S)) direction.y += 1;
	if (Keyboard::isKeyPressed(Keyboard::A)) direction.x -= 1;
	if (Keyboard::isKeyPressed(Keyboard::D)) direction.x += 1;
	physicsComponent_->setDirection(direction);
}