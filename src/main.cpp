#include <iostream>
#include <cstdlib>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb_image_write.h"
#include <enginemath/vec3.hpp>

#include "color.hpp"
#include "ray.hpp"

// Check if the ray intersects with any part of a given sphere
bool hitSphere(const enginemath::Vec3& center, double radius, const Ray& r) {
	enginemath::Vec3 oc = center - r.getOrigin();
	auto a = r.getDirection().dot(r.getDirection());
	auto b = (2 * r.getDirection()).dot(oc);
	auto c = oc.dot(oc) - radius * radius;
	auto discrim = b * b - 4 * a * c;

	// At least 1 root means the ray hit the sphere
	return (discrim >= 0);
}

// Return color for a given scene ray
color ray_color(const Ray& r) {
	if (hitSphere(enginemath::Vec3(0.0f, 0.0f, -1.0f), 0.5, r))
		return color(1.0, 0.0, 0.0);

	enginemath::Vec3 unitDirection = r.getDirection().normalized();
	auto a = 0.5 * (unitDirection.y + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}


int main() {
	// Image
	auto aspectRatio = 16.0 / 9.0;
	int imageW = 400;
	int imageH = imageW / aspectRatio;
	imageH = std::max(imageH, 1);

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

			color pixel_color = ray_color(r);
			writeColor(data, pixel_color);
		}
	}
	std::clog << "\rDone.                 \n";

	stbi_write_png("image.png", imageW, imageH, 3, data.data(), imageW * 3);
	system("start image.png");
	return 0;
}
