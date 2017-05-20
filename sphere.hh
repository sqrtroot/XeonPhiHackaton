#pragma once
#include "material.hpp"
#include "ray.hpp"
#include "coordinate.hh"
#include "material.hpp"
#include "ray.hpp"

typedef struct{
	bool hasValue;
	double value;
} intersection_optional;

class Sphere{
public:
    Coordinate origin;
    double radius;
    Material material;

    Sphere(Coordinate origin, double radius, Material material) : origin(origin),radius(radius),material(material){};


    intersection_optional intersects(Ray ray) const;

    Coordinate surface_norm(Coordinate point) const;
    
};
