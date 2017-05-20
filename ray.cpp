#include "ray.hpp"

ray::ray(Coordinate org, Coordinate dir) :
origin(org),
ray_direction(dir)
{}

Coordinate ray::point_at_dist(float dist)
{
	return origin + ray_direction * dist;
}