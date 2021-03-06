#ifndef SCENE_H
#define SCENE_H

#include "coordinate.hh"
#include "sphere.hh"
#include "ray.hpp"
#include "tbb/tbb.h"
#include <algorithm>
#include <vector>
#include <iostream>

#define dividerX 200
#define dividerY 200
#define NAIVE


struct Intersection {
	bool hasValue;
	Sphere const* obj;
	double value;
};

struct Block {
	size_t startX;
	size_t startY;
	size_t endX;
	size_t endY;
};


typedef Coordinate Color;

class Scene {
Coordinate camera;
std::vector<Sphere> objects; 
std::vector<Coordinate> lights;
int width;
int height;
public:
int traces;
	Scene(const Coordinate& camera, 
		const std::vector<Sphere>& objects,
		const std::vector<Coordinate>& lights,
		int width,
		int height): camera(camera), objects(objects), lights(lights), width(width), height(height), traces(0) {
	}

	void render(std::vector<std::vector<Coordinate>>& pixels) {
		pixels.clear();
		for (size_t i = 0; i < height; i++) {
			pixels.push_back(std::vector<Coordinate>({}));
			for (size_t j = 0; j < width; j++) {
				pixels[i].emplace_back(0,0,0);
			}
		}
#ifndef NAIVE
	std::vector<Block> blocks;
		for(int x = 0; x < dividerX; x++){
			for(int y = 0; y < dividerY; y++){
				blocks.push_back({
					x     *	(width  / dividerX + (width  % dividerX == 0 ? 0 : 1)),
					y     * (height / dividerY + (height % dividerY == 0 ? 0 : 1)),
					(x+1) * (width  / dividerX + (width  % dividerX == 0 ? 0 : 1)),
					(y+1) * (height / dividerY + (height % dividerY == 0 ? 0 : 1))
				});
			}
		}
		for(auto b : blocks){
			tbb::parallel_for(
				tbb::blocked_range<size_t>(b.startY,b.endY),
				[&](const tbb::blocked_range<size_t>& r){
					for(size_t y = r.begin(); y < r.end(); y++){
						for(size_t x = b.startX; x < b.endX; x++){
							auto ray_direction = Coordinate(x,y)-camera;
							Ray ray(camera, ray_direction);
							pixels[y][x] = trace_ray(ray);
						}
					}							
				}
			);
		}
#endif
#ifdef NAIVE
		for(size_t y = 0; y < height; y++){
			for(size_t x = 0; x < width; x++){
				auto ray_direction = Coordinate(x,y)-camera;
				Ray ray(camera, ray_direction);
				pixels[y][x] = trace_ray(ray);
			}
		}
#endif

		
		
		
		// tbb::parallel_for(
		// 	tbb::blocked_range<size_t>(0,height),
		// 	[&](const tbb::blocked_range<size_t>& r){
		// 		for(size_t y = r.begin(); y!=r.end();++y){
		// 			for(size_t x = 0; x < width; ++x){
		// 				auto ray_direction = Coordinate(x,y)-camera;
		// 				Ray ray(camera, ray_direction);
		// 				pixels[y][x] = trace_ray(ray);
		// 			}
		// 		}
		// 	}
		// );
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

	Color trace_ray(const Ray& ray, int depth = 0, int max_depth = 10) {
		
		traces++;
		Color color;
		if (depth >= max_depth)
			return color;
		Intersection intersection = _get_intersection(ray);
		if (!intersection.hasValue)
			return color;
		Sphere const* obj = intersection.obj;
		double dist = intersection.value;
		Coordinate intersection_pt = ray.point_at_dist(dist);
		Coordinate surface_norm = obj->surface_norm(intersection_pt);

		// ambient light
		color += scalar(obj->material.color, obj->material.ambient);
		// lambert shading 
		std::for_each(lights.begin(), lights.end(), [&](const Coordinate& light) {
					Coordinate pt_to_light_vec = (light - intersection_pt).normalized();
					Ray pt_to_light_ray(intersection_pt, pt_to_light_vec);
					if (!_get_intersection(pt_to_light_ray).hasValue) {
						double lambert_intensity = surface_norm * pt_to_light_vec;
						if (lambert_intensity > 0) {
							color += scalar(obj->material.color, obj->material.lambert * lambert_intensity);
						}
					}
				});
		// specular (reflective) light
		Ray reflected_ray(intersection_pt, ray.ray_direction.reflected(surface_norm).normalized());
		//reflected_ray.origin.z = - reflected_ray.origin.z;
		color += scalar(trace_ray(reflected_ray, depth+1),obj->material.specular);
		return color;
	}
};



#endif // SCENE_H
