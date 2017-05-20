#pragma once
#include "coordinate.hh"
#include "material.hpp"
#include "ray.hpp"

typedef struct{
	bool hasValue;
	float value;
} intersection_optional;

class Sphere{
public:
    Coordinate origin;
    float radius;
    Material material;

    Sphere(Coordinate origin, float radius, Material material) : origin(origin),radius(radius),material(material){};


    intersection_optional intersects(Ray ray) const;

    Coordinate surface_norm(Coordinate point) const;
    
};
