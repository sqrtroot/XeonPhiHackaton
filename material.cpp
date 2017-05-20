#include "material.hpp"

material::material(Coordinate col, float spec, float lamb, float amb) :
color(col),
specular(spec),
lambert(lamb),
ambiant(amb)
{}
