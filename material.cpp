#include "material.hpp"

Material::Material(Coordinate col, double spec, double lamb, double amb) :
color(col),
specular(spec),
lambert(lamb),
ambient(amb)
{}
