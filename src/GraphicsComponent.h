#pragma once

#include "Component.h"
#include "stdafx.h"

class GraphicsComponent : public Component{
public:
	GraphicsComponent(sf::Sprite* sprite);
	void update(int frameTime);
	void render(sf::RenderTarget* target);
private:
	std::unique_ptr<sf::Sprite> sprite_;
};