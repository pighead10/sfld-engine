#pragma once

class Projection{
public:
	Projection(float min_, float max_);
	float min, max;

	bool doesOverlap(const Projection& other) const;
	float getOverlap(const Projection& other) const;
};