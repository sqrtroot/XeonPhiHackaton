#pragma once
#include "coordinate.hh"


class Material
{
	public:
		Coordinate color;
		double specular;
		double lambert;
		double ambient;

		Material(Coordinate col, double spec=0.5, double lamb=1, double amb=0.2);
};
