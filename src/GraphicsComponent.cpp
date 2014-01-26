#include "stdafx.h"
#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(sf::Sprite* sprite){
	sprite_ = std::unique_ptr<sf::Sprite>(sprite);
}

void GraphicsComponent::update(int frameTime){
	sprite_->setPosition(parent_->getPosition());
}

void GraphicsComponent::render(sf::RenderTarget* target){
	target->draw(*sprite_);
}