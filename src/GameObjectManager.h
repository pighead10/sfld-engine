#pragma once

#include "stdafx.h"

class GraphicsComponent;
class PhysicsComponent;
class GameObject;

typedef std::unordered_map<int, GraphicsComponent*> GraphicsPtrMap;
typedef std::unordered_map<int, GameObject> GameObjectMap;

class GameObjectManager : public sf::NonCopyable{
public:
	GameObjectManager();
	~GameObjectManager();
	void updateAll(int frameTime);
	void renderAll(sf::RenderTarget* target);

	void addObject(int id,GameObject* gameObject,GraphicsComponent* graphicsComponent);
	void removeObject(int id);
	GameObjectMap* getGameObjects();
private:
	GraphicsPtrMap graphicsComponents_;
	GameObjectMap gameObjects_;
};