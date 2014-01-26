#pragma once

#include "stdafx.h"

class GraphicsComponent;
class GameObject;

typedef std::map<int, std::unique_ptr<GraphicsComponent>> GraphicsPtrMap;
typedef std::map<int, GameObject> GameObjectMap;

class GameObjectManager : public sf::NonCopyable{
public:
	GameObjectManager();
	~GameObjectManager();
	void updateAll(int frameTime);
	void renderAll(sf::RenderTarget* target);

	void addObject(int id,GameObject* gameObject,GraphicsComponent* graphicsComponent);
	void removeObject(int id);
private:
	GraphicsPtrMap graphicsComponents_;
	GameObjectMap gameObjects_;
};