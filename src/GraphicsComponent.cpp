#include "stdafx.h"
#include "GraphicsComponent.h"
#include "ComponentMessage.h"

//if this changes any properties of GameObject (size, origin) then it must set it in the GameObject

GraphicsComponent::GraphicsComponent(sf::Sprite* sprite,GameObject* parent,sf::Sprite* test):collided(false),timer(0){
	parent_ = parent;
	sprite_ = std::unique_ptr<sf::Sprite>(sprite);
	testSprite = std::unique_ptr<sf::Sprite>(test);
	parent_->setSize(sfld::Vector2f(sprite_->getGlobalBounds().width, sprite_->getGlobalBounds().height));
}

void GraphicsComponent::receive(const ComponentMessage& message){
	if (message.getMessageCategory() == ComponentMessage::CATEGORY_PHYSICS){
		if (message.getMessageType() == ComponentMessage::PHYSICS_COLLISION){
			collided = true;
			timer = 0;
		}
	}
}

void GraphicsComponent::update(int frameTime){
	timer += frameTime;
	if (timer > 200){
		collided = false;
	}
	sprite_->setPosition(parent_->getPosition());
	testSprite->setPosition(parent_->getPosition());
}

void GraphicsComponent::render(sf::RenderTarget* target){
	if (!collided){
		target->draw(*sprite_);
	}
	else{
		target->draw(*testSprite);
	}
}