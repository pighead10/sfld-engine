#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentMessage.h"

GameObject::GameObject() = default;

GameObject::GameObject(GameObject&& other) //would love to have this defaulted, but nope, visual studio 2013
	: id_(std::move(other.id_)),
	position_(std::move(other.position_)),
	components_(std::move(other.components_)){

	ComponentPtrVector::iterator it;
	for (it = components_.begin(); it != components_.end(); it++){
		(*it)->parent_ = this;
	}
}

sf::Vector2f GameObject::getPosition() const{
	return position_;
}

void GameObject::addComponent(Component* component){ //the order things are added to this is the order that things will be updated
	component->parent_ = this;
	components_.push_back(std::unique_ptr<Component>(component));
	components_.back()->parent_ = this;
}

void GameObject::update(int frameTime){
	ComponentPtrVector::iterator it;
	for(it = components_.begin();it!=components_.end();it++){
		(*it)->update(frameTime);
	}
}

void GameObject::send(const ComponentMessage& message){
	for (ComponentPtrVector::iterator it = components_.begin(); it != components_.end(); it++){
		(*it)->receive(message);
	}
}