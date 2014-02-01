#include "stdafx.h"
#include "Projection.h"

Projection::Projection(float min_, float max_)
	:min(min_), max(max_){
}

bool Projection::doesOverlap(const Projection& other) const{
	return (max > other.min && other.max > min);
}

float Projection::getOverlap(const Projection& other) const{
	//does not check for overlapping. Assumes function calling this will have already checked (as it does in SAT)
	//to prevent double checking.
	return std::min(max, other.max) - std::max(min, other.min);
}