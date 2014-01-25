#include "stdafx.h"
#include "TestState.h"
#include "StateManager.h"
#include "ResourceManager.h"

void TestState::sfmlEvent(sf::Event evt){
	switch(evt.type){
	case sf::Event::Closed:
		getParent().pop();
		break;
	default:
		break;
	}
}

void TestState::start(){
	
}

void TestState::pause(){
}


void TestState::resume(){
}

void TestState::exit(){
}

void TestState::update(int frameTime){
}

void TestState::render(sf::RenderTarget* target){
	target->clear(sf::Color::Blue);
}