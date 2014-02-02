#include "stdafx.h"
#include "TestState.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "SampleInputComponent.h"
#include "CollisionGrid.h"

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
	//TODO: -make setRotation etc send messages to components
	//		-fix collision problem where two things moving into each other will be pushed
	//		-additional testing of collisions
	gameObjectManager_ = std::unique_ptr<GameObjectManager>(new GameObjectManager());
	collisionGrid_ = std::unique_ptr<CollisionGrid>(new CollisionGrid());

	resourceManager_.setDirectory("src/media/images/");
	resourceManager_.load("test", "test.png");

	GameObject* player = new GameObject();
	GraphicsComponent* graphicsComponent = (new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), player));
	PhysicsComponent* physicsComponent = new PhysicsComponent(0.2, collisionGrid_.get());
	SampleInputComponent* inputComponent = new SampleInputComponent(physicsComponent);

	player->addPhysicsComponent(physicsComponent);
	player->addComponent(graphicsComponent);
	player->addComponent(inputComponent);
	gameObjectManager_->addObject(0, player, graphicsComponent);
	
	GameObject* block = new GameObject();
	GraphicsComponent* graphicsComponent2 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block);
	PhysicsComponent* physicsComponent2 = new PhysicsComponent(1, collisionGrid_.get());
	block->addPhysicsComponent(physicsComponent2);
	block->addComponent(graphicsComponent2);

	block->setPosition(sfld::Vector2f(300, 300));
	gameObjectManager_->addObject(1, block, graphicsComponent2);
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