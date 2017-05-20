#pragma once
#include "material.hpp"
#include "ray.hpp"
#include "coordinate.hh"
class Sphere{
public:
    Coordinate origin;
    float radius;
    Material material;

    Sphere(Coordinate origin, float radius, Material material) : origin(origin),radius(radius),material(material){};

    typedef struct{
        bool hasValue;
        float value;
    } intersection_optional;

    intersection_optional intersects(Ray ray);

    Coordinate surface_norm(Coordinate point);
    
};