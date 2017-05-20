#ifndef SCENE_H
#define SCENE_H

#include "coordinate.hh"
#include "sphere.hh"
#include "ray.hpp"
#include <algorithm>
#include <vector>


struct Intersection {
	bool hasValue;
	Sphere const* obj;
	float value;
};

typedef Coordinate Color;

class Scene {
Coordinate camera;
std::vector<Sphere> objects; 
std::vector<Coordinate> lights;
int width;
int height;
public:
	Scene(const Coordinate& camera, 
		const std::vector<Sphere>& objects,
		const std::vector<Coordinate>& lights,
		int width,
		int height);

	void render(std::vector<std::vector<Coordinate>>& pixels) {
		pixels.clear();
		for (size_t i = 0; i < height; i++) {
			pixels.push_back(std::vector<Coordinate>({}));
			for (size_t j = 0; j < height; j++) {
				pixels[i].emplace_back(0,0,0);
			}
		}

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < height; x++) {
				Coordinate ray_direction = Coordinate(x,y) - camera;
				Ray ray(camera, ray_direction);
				pixels[y][x] = trace_ray(ray);
			}
		}
	}

private:
	Intersection _get_intersection(const Ray& ray) {
		Intersection intersection{false, 0, 0.0};
		std::for_each(objects.begin(),
			      objects.end(),
				[&](const Sphere& obj) {
				intersection_optional dist = obj.intersects(ray);
				if (dist.hasValue) {
					if (!intersection.hasValue || dist.value < intersection.value) {
						intersection.hasValue = true;
						intersection.value = dist.value;
						intersection.obj = &obj;
					}
				}
		});
		return intersection;
	}

	Color trace_ray(const Ray& ray, int depth = 0, int max_depth = 5) {
		Color color;
		if (depth > max_depth)
			return color;
		Intersection intersection = _get_intersection(ray);
		if (!intersection.hasValue)
			return color;
		Sphere const* obj = intersection.obj;
		float dist = intersection.value;
		Coordinate intersection_pt = ray.point_at_dist(dist);
		Coordinate surface_norm = obj->surface_norm(intersection_pt);

		// ambient light
		color += obj->material.color * obj->material.ambient;
		// lambert shading 
		std::for_each(lights.begin(), lights.end(), [&](const Coordinate& light) {
					Coordinate pt_to_light_vec = (light - intersection_pt).normalized();
					Ray pt_to_light_ray(intersection_pt, pt_to_light_vec);
					if (!_get_intersection(pt_to_light_ray).hasValue) {
						float lambert_intensity = surface_norm * pt_to_light_vec;
						if (lambert_intensity > 0) {
							color += obj->material.color * obj->material.lambert * lambert_intensity;
						}
					}
				});
		// specular (reflective) light
		Ray reflected_ray(intersection_pt, ray.ray_direction.reflected(surface_norm).normalized());
		color += trace_ray(reflected_ray, depth+1) * obj->material.specular;
		return color;
	}
};



#endif // SCENE_H
