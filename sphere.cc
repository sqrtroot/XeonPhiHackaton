#include <cmath>
#include "sphere.hh"
#include "math.h"


intersection_optional Sphere::intersects(Ray ray) const {
    auto sphere_to_ray = ray.origin - origin;
    double b = scalar(ray.ray_direction, 2.f) * sphere_to_ray;
    double c = (sphere_to_ray * sphere_to_ray) - (radius * radius);
    double discriminant = (b*b) - 4.f * c;
    if(discriminant >= 0){
        float dist = ( (-1.f*b) - sqrt(discriminant)) / 2.f;
        if(dist > 0){
            return {true,dist};
        }
    }
    return {false,0.f};
}

Coordinate Sphere::surface_norm(Coordinate point) const{
    return (point - origin).normalized();
}
