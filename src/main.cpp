#include <iostream>
#include <cstdlib>
#include <vector>

#include "defines.h"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"


int main() {
	// World
	hittable_list world;
	
	auto material_ground = std::make_shared<lambertian>(color(0.8f, 0.8f, 0.0));
	auto material_center = std::make_shared<lambertian>(color(0.1f, 0.2f, 0.5f));
	auto material_metal = std::make_shared<metal>(color(0.8f, 0.8f, 0.8f), 0.2);
	auto material_metal2 = std::make_shared<metal>(color(0.2f, 0.8f, 0.3f), 0.9);

	world.add(std::make_shared<sphere>(enginemath::Vec3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
	world.add(std::make_shared<sphere>(enginemath::Vec3(0.0f, 0.0f, -1.2f), 0.5f, material_center));
	world.add(std::make_shared<sphere>(enginemath::Vec3(-1.0f, 0.0f, -1.0f), 0.5f, material_metal));
	world.add(std::make_shared<sphere>(enginemath::Vec3(1.0f, 0.0f, -1.0f), 0.5f, material_metal));
	world.add(std::make_shared<sphere>(enginemath::Vec3(0.0f, 1.0f, -1.0f), 0.3f, material_metal2));

	camera cam;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.imageW = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;
	cam.render(world);

	system("start image.png");
	return 0;
}
