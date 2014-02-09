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
	//		-fix collision problem where two things moving into each other will be pushed
	//		-additional testing of collisions
	gameObjectManager_ = std::unique_ptr<GameObjectManager>(new GameObjectManager());
	collisionGrid_ = std::unique_ptr<CollisionGrid>(new CollisionGrid());

	resourceManager_.setDirectory("src/media/images/");
	resourceManager_.load("test", "test.png");
	resourceManager_.load("red", "collided.png");

	GameObject* player = new GameObject();
	GraphicsComponent* graphicsComponent = (new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), player,new sf::Sprite(resourceManager_.get("red"))));
	PhysicsComponent* physicsComponent = new PhysicsComponent(0.2, collisionGrid_.get());
	SampleInputComponent* inputComponent = new SampleInputComponent(physicsComponent);

	player->addPhysicsComponent(physicsComponent);
	player->addComponent(graphicsComponent);
	player->addComponent(inputComponent);
	gameObjectManager_->addObject(0, player, graphicsComponent);
	
	GameObject* block = new GameObject();
	GraphicsComponent* graphicsComponent2 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block, new sf::Sprite(resourceManager_.get("red")));
	PhysicsComponent* physicsComponent2 = new PhysicsComponent(1, collisionGrid_.get());
	block->addPhysicsComponent(physicsComponent2);
	block->addComponent(graphicsComponent2);

	GameObject* block2 = new GameObject();
	GraphicsComponent* graphicsComponent3 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block2, new sf::Sprite(resourceManager_.get("red")));
	PhysicsComponent* physicsComponent3 = new PhysicsComponent(1, collisionGrid_.get());
	block2->addPhysicsComponent(physicsComponent3);
	block2->addComponent(graphicsComponent3);

	GameObject* block3 = new GameObject();
	GraphicsComponent* graphicsComponent4 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block3, new sf::Sprite(resourceManager_.get("red")));
	PhysicsComponent* physicsComponent4 = new PhysicsComponent(1, collisionGrid_.get());
	block3->addPhysicsComponent(physicsComponent4);
	block3->addComponent(graphicsComponent4);

	GameObject* block4 = new GameObject();
	GraphicsComponent* graphicsComponent5 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block4, new sf::Sprite(resourceManager_.get("red")));
	PhysicsComponent* physicsComponent5 = new PhysicsComponent(1, collisionGrid_.get());
	block4->addPhysicsComponent(physicsComponent5);
	block4->addComponent(graphicsComponent5);

	GameObject* block5 = new GameObject();
	GraphicsComponent* graphicsComponent6 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block5, new sf::Sprite(resourceManager_.get("red")));
	PhysicsComponent* physicsComponent6 = new PhysicsComponent(1, collisionGrid_.get());
	block5->addPhysicsComponent(physicsComponent6);
	block5->addComponent(graphicsComponent6);

	GameObject* block6 = new GameObject();
	GraphicsComponent* graphicsComponent7 = new GraphicsComponent(new sf::Sprite(resourceManager_.get("test")), block6, new sf::Sprite(resourceManager_.get("red")));
	PhysicsComponent* physicsComponent7 = new PhysicsComponent(1, collisionGrid_.get());
	block6->addPhysicsComponent(physicsComponent7);
	block6->addComponent(graphicsComponent7);

	block->setPosition(sfld::Vector2f(300, 300));
	block2->setPosition(sfld::Vector2f(332, 300));
	block3->setPosition(sfld::Vector2f(364, 300));
	block4->setPosition(sfld::Vector2f(396, 300));
	block5->setPosition(sfld::Vector2f(396, 268));
	block6->setPosition(sfld::Vector2f(396, 236));

	gameObjectManager_->addObject(6, block6, graphicsComponent7);
	gameObjectManager_->addObject(2, block2, graphicsComponent3);
	gameObjectManager_->addObject(4, block4, graphicsComponent5);
	gameObjectManager_->addObject(3, block3, graphicsComponent4);
	gameObjectManager_->addObject(1, block, graphicsComponent2);
	gameObjectManager_->addObject(5, block5, graphicsComponent6);
	
	
	
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