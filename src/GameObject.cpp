#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentMessage.h"
#include "PhysicsComponent.h"

GameObject::GameObject()
	: rotation_(0), id_(0), physicsComponent_(NULL){
}

GameObject::GameObject(GameObject&& other) //would love to have this defaulted, but nope, visual studio 2013
	: id_(std::move(other.id_)),
	position_(std::move(other.position_)),
	components_(std::move(other.components_)),
	rotation_(std::move(other.rotation_)),
	physicsComponent_(std::move(other.physicsComponent_)),
	origin_(std::move(other.origin_)),
	size_(std::move(other.size_))
	{

	ComponentPtrVector::iterator it;
	for (it = components_.begin(); it != components_.end(); it++){
		(*it)->parent_ = this;
	}
}

GameObject::~GameObject(){
	//so that the component's destructors can use GameObject's properties
	ComponentPtrVector::iterator it;
	for (it = components_.begin(); it != components_.end();){
		components_.erase(it);
	}
}

sfld::Vector2f GameObject::getSize() const{
	return size_;
}

void GameObject::setSize(const sfld::Vector2f& size){
	size_ = size;
}

void GameObject::setRotation(float degrees){
	rotation_ = degrees;
	MessageInfo info;
	info["degrees"] = &degrees;
	send(ComponentMessage(ComponentMessage::CATEGORY_PHYSICS, ComponentMessage::PHYSICS_ROTATION, info));
}

float GameObject::getRotation() const{
	return rotation_;
}

sfld::Vector2f GameObject::getPosition() const{
	return position_;
}

sfld::Vector2f GameObject::getOrigin() const{
	return origin_;
}

void GameObject::setOrigin(const sfld::Vector2f& origin){
	origin_ = origin;
	MessageInfo info;
	info["origin"] = &sfld::Vector2f(origin);
	send(ComponentMessage(ComponentMessage::CATEGORY_AI, ComponentMessage::PHYSICS_ORIGIN, info));
}

void GameObject::move(const sfld::Vector2f& offset){
	setPosition(getPosition() + offset);
}

void GameObject::setPosition(const sfld::Vector2f& position){
	if (hasPhysics()){
		physicsComponent_->moveOnGrid(position);
	}
	position_ = position;
}

bool GameObject::hasPhysics() const{
	return physicsComponent_ != NULL;
}

void GameObject::clean(){
	send(ComponentMessage(ComponentMessage::CATEGORY_MISC, ComponentMessage::MISC_CLEAN, MessageInfo()));
}

sf::FloatRect GameObject::getBoundings() const{
	return sf::FloatRect(getPosition().x, getPosition().y, getSize().x, getSize().y);
}

void GameObject::addComponent(Component* component){ //the order things are added to this is the order that things will be updated
	component->parent_ = this;
	components_.push_back(std::unique_ptr<Component>(component));
	components_.back()->parent_ = this;
}

void GameObject::addPhysicsComponent(PhysicsComponent* component){
	addComponent(component);
	physicsComponent_ = component;
	physicsComponent_->addToGrid(getPosition());
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