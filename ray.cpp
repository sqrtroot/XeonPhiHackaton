#include "ray.hpp"

Ray::Ray(Coordinate org, Coordinate dir) :
origin(org),
ray_direction(dir.normalized())
{}

Coordinate Ray::point_at_dist(double dist) const
{
	return origin + (ray_direction * dist);
}
