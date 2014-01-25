#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

void GameObject::addComponent(Component* component){ //order is important when adding to this
	components_.push_back(std::unique_ptr<Component>(component));
}

void GameObject::update(int frameTime){
	std::vector<std::unique_ptr<Component>>::iterator it;
	for(it = components_.begin();it!=components_.end();it++){
		(*it)->update(frameTime);
	}
}