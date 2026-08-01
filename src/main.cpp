#include <iostream>
#include <cstdlib>
#include <vector>

#include "defines.h"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"


int main() {
	// World
	hittable_list world;
	world.add(std::make_shared<sphere>(enginemath::Vec3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(enginemath::Vec3(0, -100.5, -1), 100));

	camera cam;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.imageW = 400;
	cam.samples_per_pixel = 100;
	cam.render(world);

	system("start image.png");
	return 0;
}
