#include "scene.hh"
#include "ppm.hpp"
#include "sphere.hh"

int main(int argc, char* argv[]) {
	std::vector<Sphere> objects{
		Sphere(Coordinate(150, 120, -20), 80, Material(Color(0xFF, 0, 0), 0.2, 0.0, 0.0)),
		Sphere(Coordinate(420, 120, 0), 100, Material(Color(0, 0, 0xFF), 0.8, 0.0, 0.0)),
		Sphere(Coordinate(320, 240, -40), 50, Material(Color(0, 0xFF, 0), 0.0, 0.0, 0.0)),
		Sphere(Coordinate(300, 200, 200), 100, Material(Color(0xFF, 0xFF, 0), 0.8, 0.0, 0.0)),
		Sphere(Coordinate(300, 130, 100), 40, Material(Color(0xFF, 0, 0xFF), 0.0, 0.0, 0.0)),
		Sphere(Coordinate(300, 1000, 0), 700, Material(Color(0xFF, 0xFF, 0xFF), 0.0, 0.5, 0.0))
	};
	std::vector<Coordinate> lights{
		Coordinate(200, -100, 0), Coordinate(600, 200, -200)
	};
	Coordinate camera(200, 200, -400);
	Scene scene(camera, objects, lights, 600, 400);
	std::vector<std::vector<Coordinate>> pixels;
	scene.render(pixels);
	pixels_to_ppm(pixels);
	return 0;
}
