#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GraphicsComponent.h"

GameObjectManager::GameObjectManager() = default;

GameObjectManager::~GameObjectManager() = default;

void GameObjectManager::updateAll(int frameTime){
	std::map<int,GameObject>::iterator it;
	for(it = gameObjects_.begin();it != gameObjects_.end();it++){
		it->second.update(frameTime);
	}
}

void GameObjectManager::addObject(int id,GameObject* gameObject,GraphicsComponent* graphicsComponent){ //graphicsComponent can be NULL. *gameObject is left blank.
	assert(gameObjects_.count(id) == 0 && "Attempted to insert a GameObject with the same id as a previous object!");
	gameObjects_.insert(std::make_pair(id,std::move(*gameObject)));
	if (graphicsComponent != NULL){
		graphicsComponents_[id] = std::unique_ptr<GraphicsComponent>(graphicsComponent);
	}
}

void GameObjectManager::removeObject(int id){
	GameObjectMap::iterator result = gameObjects_.find(id);
	
	if (result == gameObjects_.end()){
		std::cout << "Attempted to remove object with id " << id << ", but no item in the map has that id." << std::endl;
	}
	else{
		GraphicsPtrMap::iterator result = graphicsComponents_.find(id);
		if (result != graphicsComponents_.end()){
			graphicsComponents_.erase(id);
		}
		gameObjects_.erase(id);
	}
}

void GameObjectManager::renderAll(sf::RenderTarget* target){
	std::map<int,std::unique_ptr<GraphicsComponent>>::iterator it;
	for(it = graphicsComponents_.begin();it!=graphicsComponents_.end();it++){
		it->second->render(target);
	}
}
