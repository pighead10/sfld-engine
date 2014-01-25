#pragma once

#include "stdafx.h"

class GraphicsComponent;
class GameObject;

class GameObjectManager : public sf::NonCopyable{
public:

	void updateAll(int frameTime);
	void renderAll(sf::RenderTarget* target);

	void addObject(int id,GameObject* gameObject,GraphicsComponent* graphicsComponent);
	void removeObject(int id);
private:
	std::map<int,std::unique_ptr<GraphicsComponent>> graphicsComponents_;
	std::map<int,GameObject> gameObjects_;
};