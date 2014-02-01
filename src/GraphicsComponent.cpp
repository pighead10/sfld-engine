#include "stdafx.h"
#include "GraphicsComponent.h"

//if this changes any properties of GameObject (size, origin) then it must set it in the GameObject

GraphicsComponent::GraphicsComponent(sf::Sprite* sprite,GameObject* parent){
	parent_ = parent;
	sprite_ = std::unique_ptr<sf::Sprite>(sprite);
	parent_->setSize(sfld::Vector2f(sprite_->getGlobalBounds().width, sprite_->getGlobalBounds().height));
}

void GraphicsComponent::update(int frameTime){
	sprite_->setPosition(parent_->getPosition());
}

void GraphicsComponent::render(sf::RenderTarget* target){
	target->draw(*sprite_);
}