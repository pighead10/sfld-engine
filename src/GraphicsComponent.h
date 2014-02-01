#pragma once

#include "Component.h"
#include "stdafx.h"

//can inherit from this to put different graphics elements on your objects

class GraphicsComponent : public Component{
public:
	explicit GraphicsComponent(sf::Sprite* sprite,GameObject* parent);
	virtual void update(int frameTime);
	virtual void render(sf::RenderTarget* target);
private:
	std::unique_ptr<sf::Sprite> sprite_;
};