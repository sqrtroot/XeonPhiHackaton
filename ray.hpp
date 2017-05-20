#pragma once
#include "coordinate.hh"

class Ray
{
public:
	Coordinate origin;
	Coordinate ray_direction;

	Ray(Coordinate org, Coordinate dir);

	Coordinate point_at_dist(float dist) const;
};
