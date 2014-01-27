#pragma once

#include "Component.h"

class PhysicsComponent;

class SampleInputComponent : public Component{
public:
	explicit SampleInputComponent(PhysicsComponent* physicsComponent);
	void update(int frameTime);
private:
	PhysicsComponent* physicsComponent_;
};