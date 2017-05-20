#include <cmath>
#include "sphere.hh"
intersection_optional Sphere::intersects(Ray ray){
    auto sphere_to_ray = ray.origin - origin;
    float b = 2.f * ray.direction * sphere_to_ray;
    float c = pow(sphere_to_ray,2) - pow(radius,2);
    float discriminant = pow(b,2) - 4.f * c;
    if(discriminant >= 0){
        float dist = ( -1.f*b - sqrt(discriminant)) / 2.f;
        if(dist > 0){
            return {true,dist};
        }
    }
    return {false,0.f};
}

Coordinate Sphere::surface_norm(Coordinate point){
    return (point - origin).normalized();
}