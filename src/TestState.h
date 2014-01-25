#pragma once

#include "BaseState.h"
#include "ResourceManager.h"

class TestState : public BaseState{
public:
	void sfmlEvent(sf::Event evt);

	void start();
	void pause();
	void resume();
	void exit();

	void update(int frameTime);
	void render(sf::RenderTarget* target);
private:
	//vector of the game objects... but how do objects get added to it?
	ResourceManager<sf::Texture,std::string> resourceManager_;
};