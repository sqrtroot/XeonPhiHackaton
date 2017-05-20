#include "ray.hpp"

Ray::Ray(Coordinate org, Coordinate dir) :
origin(org),
ray_direction(dir)
{}

Coordinate Ray::point_at_dist(float dist) const
{
	return origin + ray_direction * dist;
}
