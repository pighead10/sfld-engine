#include "stdafx.h"
#include "CollisionGrid.h"
#include "PhysicsComponent.h"

CollisionGrid::CollisionGrid(){
}

void CollisionGrid::add(const sfld::Vector2f& pos, PhysicsComponent* object){
	sf::Vector2i gridPosition((int)pos.x / TILE_SIZE, (int)pos.y / TILE_SIZE);
	grid_[std::make_pair(gridPosition.x,gridPosition.y)].push_back(object);
}

void CollisionGrid::move(const sfld::Vector2f& startPosition, const sfld::Vector2f& endPosition, PhysicsComponent* object){
	sf::Vector2i startGridPosition((int)startPosition.x / TILE_SIZE, (int)startPosition.y / TILE_SIZE);
	sf::Vector2i endGridPosition((int)endPosition.x / TILE_SIZE, (int)endPosition.y / TILE_SIZE);

	if (startGridPosition != endGridPosition){
		remove(startPosition, object);
		add(endPosition, object);
	}
}

void CollisionGrid::remove(const sfld::Vector2f& position, PhysicsComponent* object){
	sf::Vector2i gridPosition((int)position.x / TILE_SIZE, (int)position.y / TILE_SIZE);

	PhysicsContainer::iterator it;
	PhysicsContainer* objectGrid = &grid_[std::make_pair(gridPosition.x,gridPosition.y)];
	for (it = objectGrid->begin(); it != objectGrid->end();it++){
		if (object == *it){
			objectGrid->erase(it);
			break;
		}
	}
}

PhysicsContainer CollisionGrid::getPotentialCollisions(const sfld::FloatOrientedRect& bounds){
	std::map<std::pair<int,int>, bool> areasToCheck;
	
	for (int x = -1; x <= 1; x++){
		for (int y = -1; y <= 1; y++){
			areasToCheck[std::make_pair((int)bounds.getTopLeft().x / TILE_SIZE + x, (int)bounds.getTopLeft().y / TILE_SIZE + y)] = true;
			areasToCheck[std::make_pair((int)bounds.getTopRight().x / TILE_SIZE + x, (int)bounds.getTopRight().y / TILE_SIZE + y)] = true;
			areasToCheck[std::make_pair((int)bounds.getBotLeft().x / TILE_SIZE + x, (int)bounds.getBotLeft().y / TILE_SIZE + y)] = true;
			areasToCheck[std::make_pair((int)bounds.getTopRight().x / TILE_SIZE + x, (int)bounds.getTopRight().y / TILE_SIZE + y)] = true;
		}
	}

	PhysicsContainer objects;

	std::map<std::pair<int,int>, bool>::iterator it;
	for (it = areasToCheck.begin(); it != areasToCheck.end(); it++){
		PhysicsContainer* gridObjects = &grid_[std::make_pair(it->first.first,it->first.second)];
		objects.insert(objects.end(), gridObjects->begin(), gridObjects->end());
	}

	return objects;
}