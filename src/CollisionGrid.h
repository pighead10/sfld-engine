#pragma once

#include "stdafx.h"
#include "OrientedRectangle.h"

class PhysicsComponent;
class GameObject;

typedef std::vector<PhysicsComponent*> PhysicsContainer;
typedef std::map<std::pair<int,int>, PhysicsContainer> GridContainer;

class CollisionGrid{
public:
	CollisionGrid();
	void add(const sfld::Vector2f& pos, PhysicsComponent* object);
	void move(const sfld::Vector2f& startPosition, const sfld::Vector2f& endPosition, PhysicsComponent* object);
	void remove(const sfld::Vector2f& position, PhysicsComponent* object);
	PhysicsContainer getPotentialCollisions(const sfld::FloatOrientedRect& bounds);
private:
	static const int TILE_SIZE = 64;
	GridContainer grid_;
};