#include "coordinate.hh"

#pragma once

class Ray
{
public:
	Coordinate origin;
	Coordinate ray_direction;

	Ray(Coordinate org, Coordinate dir);

	Coordinate point_at_dist(float dist) const;
};
