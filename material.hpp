#pragma once
#include "coordinate.hh"


class Material
{
	public:
		Coordinate color;
		float specular;
		float lambert;
		float ambient;

		Material(Coordinate col, float spec=0.5, float lamb=1, float amb=0.2);
};
