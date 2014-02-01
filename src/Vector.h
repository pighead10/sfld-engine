//sfml's vector class, but with typical vector functions (dot product, roation, etc)

#pragma once

#include <SFML/System/Vector2.hpp>

namespace sfld{
	template<typename T>
	class Vector2 : public sf::Vector2<T>{
	public:
		Vector2();
		Vector2(T X, T Y);
		Vector2(const sf::Vector2<T>& vector); //intentional implicit conversion
		Vector2<T> rotate(float degrees);
		Vector2<T> rotate(float degrees, const Vector2<T>& origin);
		float dot(const Vector2<T>& other) const;
		Vector2<T> normalise() const;
		float length() const;
		Vector2<T> perpendicular() const;
		Vector2<T> lerp(const Vector2<T>& start, const Vector2<T>& end, float percent) const;
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
}

#include "Vector.inl"