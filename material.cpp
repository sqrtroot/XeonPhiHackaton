#include "material.hpp"

Material::Material(Coordinate col, float spec, float lamb, float amb) :
color(col),
specular(spec),
lambert(lamb),
ambient(amb)
{}
