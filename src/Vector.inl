#include "stdafx.h"

using namespace sfld;

template<typename T>
Vector2<T>::Vector2(){
	x = 0;
	y = 0;
}

template<typename T>
Vector2<T>::Vector2(T X,T Y){
	x = X;
	y = Y;
}

template<typename T>
float Vector2<T>::dot(const Vector2<T>& other) const{
	return (x * other.x) + (y * other.y);
}

template<typename T>
Vector2<T> Vector2<T>::normalise() const{
	float len = length();
	return Vector2<T>(x / len, y / len);
}

template<typename T>
float Vector2<T>::length() const{
	return sqrt(x*x + y*y);
}

template<typename T>
Vector2<T> Vector2<T>::lerp(const Vector2<T>& start, const Vector2<T>& end, float percent) const{
	return start + percent*(end - start);
}