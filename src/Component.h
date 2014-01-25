#pragma once

#include "stdafx.h"

class Component : public sf::NonCopyable{
public:
	virtual void update(int frameTime) = 0;
};