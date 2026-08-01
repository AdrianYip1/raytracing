#include <iostream>
#include <cstdlib>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb_image_write.h"

#include "defines.h"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

color ray_color(const Ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, interval(0, infinity), rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	enginemath::Vec3 unit_dir = r.getDirection().normalized();
	auto a = 0.5 * (unit_dir.y + 1);
	return (1- a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}


int main() {
	// Image
	auto aspectRatio = 16.0 / 9.0;
	int imageW = 400;
	int imageH = imageW / aspectRatio;
	imageH = std::max(imageH, 1);

	// World

	hittable_list world;

	world.add(std::make_shared<sphere>(enginemath::Vec3(0, 0, -1), 0.5));

	world.add(std::make_shared<sphere>(enginemath::Vec3(0, -100.5, -1), 100));

	// Camrea
	auto focalLength = 1.0;
	auto viewportH = 2.0;
	auto viewportW = viewportH * ((double)imageW / imageH);
	auto cameraCenter = enginemath::Vec3(0);

	auto viewportU = enginemath::Vec3(viewportW, 0, 0);
	auto viewportV = enginemath::Vec3(0, -viewportH, 0);

	auto pixelDu = viewportU / imageW;
	auto pixelDv = viewportV / imageH;

	// Upper left pixel of viewport
	auto viewportUpperLeft = cameraCenter - 
							 enginemath::Vec3(0, 0, focalLength) -
							 viewportU/2 - viewportV/2;
	// the center of the upper left pixel
	auto pixel00_loc = viewportUpperLeft + (0.5 * (pixelDu + pixelDv));

	std::vector<unsigned char> data;
	data.reserve(imageW * imageH * 3);

	// Render
	for (int j = 0; j < imageH; j++) {
		std::clog << "\rScanlines remaining: " << (imageH - j) << " " << std::flush;
		for (int i = 0; i < imageW; i++) {
			auto pixelCenter = pixel00_loc + (j * pixelDv) + (i * pixelDu);
			auto rayDirection = pixelCenter - cameraCenter;
			Ray r(cameraCenter, rayDirection);

			color pixel_color = ray_color(r, world);
			writeColor(data, pixel_color);
		}
	}
	std::clog << "\rDone.                 \n";

	stbi_write_png("image.png", imageW, imageH, 3, data.data(), imageW * 3);
	system("start image.png");
	return 0;
}
