#pragma once

#include "BaseState.h"
#include "ResourceManager.h"

class GameObjectManager;
class CollisionGrid;

class TestState : public BaseState{
public:
	TestState();
	~TestState();
	void sfmlEvent(sf::Event evt);

	void start();
	void pause();
	void resume();
	void exit();

	void update(int frameTime);
	void render(sf::RenderTarget* target);
private:
	std::unique_ptr<CollisionGrid> collisionGrid_;
	std::unique_ptr<GameObjectManager> gameObjectManager_;
	ResourceManager<sf::Texture,std::string> resourceManager_;
};