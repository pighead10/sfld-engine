#pragma once

#include "Vector.h"

class Projection;

namespace sfld{
	template<typename T>
	class OrientedRect{ //TODO: add contains(), outside(), intersects(), etc...
	public:
		OrientedRect();
		OrientedRect(const sf::Rect<T>& bounds, const sfld::Vector2<T>& origin, float rotationDegrees);
		sfld::Vector2<T> getTopLeft() const;
		sfld::Vector2<T> getTopRight() const;
		sfld::Vector2<T> getBotLeft() const;
		sfld::Vector2<T> getBotRight() const;
		sfld::Vector2<T> checkForSATCollision(const sfld::OrientedRect<T>& other) const; //expensive
		Projection project(const sfld::Vector2<T>& axis) const;
	private:
		sfld::Vector2<T> top_left;
		sfld::Vector2<T> bot_right;
	};
	typedef OrientedRect<float> FloatOrientedRect;
	typedef OrientedRect<int> IntOrientedRect;
}

#include "OrientedRectangle.inl"