#pragma once
#include "coordinate.hh"


class ray
{
public:
	Coordinate origin;
	Coordinate ray_direction;

	ray(Coordinate org, Coordinate dir);

	Coordinate point_at_dist(float dist);
};
