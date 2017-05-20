#include "coordinate.hh"

#pragma once
class Material
{
	public:
		Coordinate color;
		float specular;
		float lambert;
		float ambient;

		Material(Coordinate col, float spec, float lamb, float amb);
};
