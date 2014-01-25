#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GraphicsComponent.h"

void GameObjectManager::updateAll(int frameTime){
	std::map<int,GameObject>::iterator it;
	for(it = gameObjects_.begin();it != gameObjects_.end();it++){
		it->second.update(frameTime);
	}
}

void GameObjectManager::addObject(int id,GameObject* gameObject,GraphicsComponent* graphicsComponent){
	//assert(gameObjects_.
	gameObjects_.insert(std::make_pair(id,std::move(*gameObject)));
	graphicsComponents_[id] = std::unique_ptr<GraphicsComponent>(graphicsComponent);
}

void GameObjectManager::removeObject(int id){
	//gameObjects_.erase(
}

void GameObjectManager::renderAll(sf::RenderTarget* target){
	std::map<int,std::unique_ptr<GraphicsComponent>>::iterator it;
	for(it = graphicsComponents_.begin();it!=graphicsComponents_.end();it++){
		it->second->render(target);
	}
}
