#include "stdafx.h"
#include "Projection.h"

using namespace sfld;

template<typename T>
OrientedRect<T>::OrientedRect(){
}

template<typename T>
OrientedRect<T>::OrientedRect(const sf::Rect<T>& bounds, const sfld::Vector2<T>& origin, float rotationDegrees){
	top_left = sfld::Vector2<T>(bounds.left, bounds.top).rotate(rotationDegrees, origin);
	bot_right = sfld::Vector2<T>(bounds.left + bounds.width, bounds.top + bounds.height).rotate(rotationDegrees, origin);
}

template<typename T>
Projection OrientedRect<T>::project(const Vector2<T>& axis) const{
	//more accurate projections if axis is normalised
	std::vector<Vector2<T>> vertices;
	vertices.push_back(getTopLeft());
	vertices.push_back(getTopRight());
	vertices.push_back(getBotLeft());
	vertices.push_back(getBotRight());

	float min = axis.dot(vertices[0]);
	float max = min;

	std::vector<Vector2<T>>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it++){
		float dot = axis.dot((*it));
		if (dot < min){
			min = dot;
		}
		else if(dot > max){
			max = dot;
		}
	}

	return Projection(min, max);
}

//returns minimum translation vector
template<typename T>
Vector2<T> OrientedRect<T>::checkForSATCollision(const OrientedRect<T>& other) const{
	std::vector<Vector2<T>> axes;
	axes.push_back((sfld::Vector2<T>(getTopRight() - getTopLeft()).perpendicular()).normalise());
	axes.push_back((sfld::Vector2<T>(getTopLeft() - getBotLeft()).perpendicular()).normalise());
	axes.push_back((sfld::Vector2<T>(other.getTopRight() - other.getTopLeft()).perpendicular()).normalise());
	axes.push_back((sfld::Vector2<T>(other.getTopLeft() - other.getBotLeft()).perpendicular()).normalise());

	float overlap = FLT_MAX;
	Vector2<T> smallestAxis;

	std::vector<Vector2<T>>::iterator it;
	for (it = axes.begin(); it != axes.end(); it++){
		Projection p1 = project(*it);
		Projection p2 = other.project(*it);
		if (!p1.doesOverlap(p2)){
			return Vector2<T>(0, 0);
		}
		else{
			float o = p1.getOverlap(p2);
			if (o < overlap){
				overlap = o;
				smallestAxis = *it;
			}
		}
	}

	return smallestAxis*(T)overlap;
}

template<typename T>
Vector2<T> OrientedRect<T>::getTopLeft() const{
	return top_left;
}

template<typename T>
Vector2<T> OrientedRect<T>::getTopRight() const{
	return sfld::Vector2f(bot_right.x, top_left.y);
}

template<typename T>
Vector2<T> OrientedRect<T>::getBotLeft() const{
	return sfld::Vector2f(top_left.x, bot_right.y);
}

template<typename T>
Vector2<T> OrientedRect<T>::getBotRight() const{
	return bot_right;
}