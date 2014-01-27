#include "stdafx.h"
#include "TestState.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "SampleInputComponent.h"

TestState::TestState() = default;
TestState::~TestState() = default;

void TestState::sfmlEvent(sf::Event evt){
	switch(evt.type){
	case sf::Event::Closed:
		getParent().pop();
		break;
	default:
		break;
	}
}

void TestState::start(){
	gameObjectManager_ = std::unique_ptr<GameObjectManager>(new GameObjectManager());

	resourceManager_.setDirectory("src/media/images/");
	resourceManager_.load("test", "test.png");

	GameObject* gameObject = new GameObject();
	GraphicsComponent* graphicsComponent = (new GraphicsComponent(new sf::Sprite(resourceManager_.get("test"))));
	PhysicsComponent* physicsComponent = new PhysicsComponent(1);
	SampleInputComponent* inputComponent = new SampleInputComponent(physicsComponent);

	gameObject->addComponent(graphicsComponent);
	gameObject->addComponent(physicsComponent);
	gameObject->addComponent(inputComponent);
	gameObjectManager_->addObject(1,gameObject,graphicsComponent);
}

void TestState::pause(){
}


void TestState::resume(){
}

void TestState::exit(){
}

void TestState::update(int frameTime){
	gameObjectManager_->updateAll(frameTime);
}

void TestState::render(sf::RenderTarget* target){
	gameObjectManager_->renderAll(target);
}